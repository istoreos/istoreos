cat << EOF

 Welcome to iStoreOS!
EOF

if [ -x /usr/sbin/quickstart ] ; then
cat << EOF
Run "quickstart" to launch the basic configuration wizard.
EOF
fi

cat << EOF
Official Website: https://www.istoreos.com

EOF
