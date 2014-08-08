bbxyard sdk - bbxyard@gmail.com
Copyright 2014 bbxyard Inc.
web: https://github.com/bbxyard/sdk
git: git@github.com:bbxyard/sdk.git


bbxyard-sdk
============================
  It assembles some useful C++/C library 
  so as to quickly establish Linux/Unix development environment.
  It includes
    apr, apr-util,  // apache portable runtime 
    curl,           // url/uri get,post,upload ...
    protobuf,       // Google Protocol Buffer, quick serialize and deserialize
    htmlcxx,        // html parser library
    ...
  librarys.


dir struct
============================
  |
  |--stub          # original package
  |--examples      # examples for verifying and demo library usage
  |--info          # [generated] store installed filelist so as to green remove
  |--include       # [generated] ... 
  |--lib           # [generated] ... for LD_LIBRARY_PATH (*.a, *.la)
  |   |--pkgconfig # [generated] ... for PKG_CONFIG_PATH (*.pc)
  |--dylib         # [generated] ... for LD_LIBRARY_PATH (*.so, *.dylib)
  |--bin           # [generated] ... demo library self
  |--build-1       # [generated] ...
  |--share         # [generated] ... for "man"
  |sdk.env         # [generated] sdk env config


sdk.env
============================
  # define or expand LD_LIBRARY_PATH, PKG_CONFIG_PATH
  export SDK_HOME=/Users/bbxyard/devhome/sdk
  export PATH=$SDK_HOME/bin:$PATH
  export LD_LIBRARY_PATH=$SDK_HOME/lib:$SDK_HOME/dylib:$LD_LIBRARY_PATH
  export PKG_CONFIG_PATH=$SDK_HOME/lib/pkgconfig:$PKG_CONFIG_PATH 


clone, build and install
============================
  $ mkdir ~/devhome #can changed!!
  $ pushd ~/devhome
  $   git clone git@github.com:bbxyard/sdk.git
  $ pushd sdk/stub
  $   ./builder.sh
  $ popd
  $ popd
  
  Everything finished!
  There is a bash env file which is located at "$HOME/devhome/sdk/sdk.env" will be generated.
  What's more, this env file has been appended to the current bash env script!
  i.e. ~/.bash_profile or ~/.bashrc which depends on your system.


verify library
============================
  # you should refresh env first.
  # Redhat/Suse/MacOS
  $ . ~/.bash_profile
  # Ubuntu/Linuxmint/Debian 
  $ . ~/.bashrc
  
  # make demo
  $ pushd $SDK_HOME
  $ cd examples
  $ make
  $ popd
  
  If no errors was showed, you made it!
  Enjoy it!!
