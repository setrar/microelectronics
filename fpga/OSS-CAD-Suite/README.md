# [oss-cad-suite-build](https://github.com/YosysHQ/oss-cad-suite-build)



### MacOS


#### Installation

Download an archive matching your OS from the releases page.

```
cd ~/bin
```

```
wget https://github.com/YosysHQ/oss-cad-suite-build/releases/download/2024-03-30/oss-cad-suite-darwin-arm64-20240330.tgz -o ~/bin/oss-cad-suite-darwin-arm64-20240330.tgz
```

Extract the archive to a location of your choice (for Windows it is recommended that path does not contain spaces)


On macOS to allow execution of quarantined files 
```
xattr -d com.apple.quarantine oss-cad-suite-darwin-x64-yyymmdd.tgz
```
 on downloaded file, or run: `./activate` in extracted location once.

```
tar zxvf ~/bin/oss-cad-suite-darwin-arm64-20240330.tgz
```

Set the environment as described below.
Linux and macOS

extracted_location=~/bin/oss-cad-suite

```
export PATH="$extracted_location/oss-cad-suite/bin:$PATH"
```

# or

source $extracted_location/oss-cad-suite/environment

