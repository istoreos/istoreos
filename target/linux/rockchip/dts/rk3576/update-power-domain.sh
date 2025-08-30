#!/bin/bash

# Extract power-domains nodes from device tree and create override dtsi
# Usage: ./extract-power-domains.sh <input_dtsi> [output_dtsi]

set -e

INPUT_FILE="../../files/arch/arm64/boot/dts/rockchip/rk3576.dtsi"
OUTPUT_FILE="rk3576-no-power-domain.dtsi"

if [ -z "$INPUT_FILE" ]; then
    echo "Usage: $0 <input_dtsi> [output_dtsi]"
    echo "Example: $0 rk3576.dtsi rk3576-no-power-domain.dtsi"
    exit 1
fi

if [ ! -f "$INPUT_FILE" ]; then
    echo "Error: Input file '$INPUT_FILE' not found"
    exit 1
fi

echo "Analyzing $INPUT_FILE for nodes with power-domains properties..."

# Create temporary file
TEMP_FILE=$(mktemp)

# Extract node labels with power-domains property
# This approach is more reliable and simpler
grep -n "power-domains" "$INPUT_FILE" | while read -r line; do
    line_num=$(echo "$line" | cut -d: -f1)
    
    # Look backward from the power-domains line to find the node definition
    for ((i=line_num; i>=1; i--)); do
        current_line=$(sed -n "${i}p" "$INPUT_FILE")
        
        # Skip empty lines and comments
        if echo "$current_line" | grep -qE '^\s*(//|/\*|\*|$)'; then
            continue
        fi
        
        # Look for node definition with label
        if echo "$current_line" | grep -qE '^\s*[a-zA-Z_][a-zA-Z0-9_]*\s*:'; then
            # Extract just the label part (before the colon)
            label=$(echo "$current_line" | grep -oE '[a-zA-Z_][a-zA-Z0-9_]*\s*:' | grep -oE '[a-zA-Z0-9_]*')
            echo "$label"
            break
        fi
        
        # If we hit another closing brace, we've gone too far
        if echo "$current_line" | grep -q '}' && [ $i -lt $((line_num - 1)) ]; then
            break
        fi
    done
done | sort | uniq > "$TEMP_FILE"

# Count found nodes
NODE_COUNT=$(wc -l < "$TEMP_FILE" 2>/dev/null || echo "0")

if [ "$NODE_COUNT" -eq 0 ]; then
    echo "No labeled nodes with power-domains property found in $INPUT_FILE"
    rm -f "$TEMP_FILE"
    exit 0
fi

echo "Found $NODE_COUNT labeled nodes with power-domains property:"
cat "$TEMP_FILE" | sed 's/^/  - /'

# Generate the output dtsi file
echo ""
echo "Generating $OUTPUT_FILE..."

# Create the header
cat > "$OUTPUT_FILE" << EOF
// SPDX-License-Identifier: (GPL-2.0+ OR MIT)
/*
 * Device tree override to remove power-domains properties
 * Auto-generated on $(date -u '+%Y-%m-%d %H:%M:%S') UTC
 * Source: $INPUT_FILE
 */

#define DT_RK3576_NO_POWER_DOMAINS

&power {
	status = "disabled";
};

EOF

# Add delete-property statements for each node
while IFS= read -r label; do
    if [ -n "$label" ]; then
        cat >> "$OUTPUT_FILE" << EOF
&${label} {
	/delete-property/ power-domains;
};

EOF
    fi
done < "$TEMP_FILE"

# Clean up
rm -f "$TEMP_FILE"

echo "Successfully created $OUTPUT_FILE with $NODE_COUNT node overrides"
echo ""
echo "Usage: Include this file in your board dtsi with:"
echo "  #include \"$OUTPUT_FILE\""
echo ""
echo "Generated file contents:"
echo "========================"
cat "$OUTPUT_FILE"