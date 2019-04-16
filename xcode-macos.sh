
cmakeImpl() {
	cmake -E make_directory "build-macos" && cmake -E chdir "build-macos" cmake -G "Xcode" ../ $1
}

if [ "$1" == "test" ] ; then
	cmakeImpl -DSXB_TEST=true
else
	cmakeImpl -DSXB_TEST=false
fi
