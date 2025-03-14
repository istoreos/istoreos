# grep -onE '<\s*GIC_[SP]PI\s+[0-9]+\s+\w+\s+&?\w+\s*>' *.dts *.dtsi

if grep -onE '<\s*GIC_[SP]PI\s+[0-9]+\s+\w+\s*>' rk3588*.dts rk3588*.dtsi >&2 ; then
	echo >&2
	echo "ERROR: RK3588 dts interrupt-cells is 4" >&2
	echo "  But some files in dts/rk3588 only have 3 cells, see above!" >&2
	exit 1
fi

exit 0
