# openFPGA

## Run

```sh
nextpnr-ice40 --version
```
> "nextpnr-ice40" -- Next Generation Place and Route (Version 20241022 (9c2d96f8))

## Install

```sh
brew tap twam/openfpga
```
>
```powershell
==> Tapping twam/openfpga
Cloning into '/opt/homebrew/Library/Taps/twam/homebrew-openfpga'...
remote: Enumerating objects: 349, done.
remote: Counting objects: 100% (231/231), done.
remote: Compressing objects: 100% (105/105), done.
remote: Total 349 (delta 102), reused 197 (delta 68), pack-reused 118 (from 1)
Receiving objects: 100% (349/349), 46.11 KiB | 1.71 MiB/s, done.
Resolving deltas: 100% (149/149), done.
Tapped 7 formulae (18 files, 68.5KB).
```

```sh
brew install nextpnr --with-gui --without-arch-ecp5
```
>
```powershell
==> Downloading https://formulae.brew.sh/api/formula.jws.json
==> Downloading https://formulae.brew.sh/api/cask.jws.json
==> Fetching dependencies for twam/openfpga/nextpnr: cmake, icu4c@77, xz, boost, python@3.13, boost-python3, pkgconf, libusb, twam/openfpga/icestorm, libgit2, llvm@19, rust, twam/openfpga/prjoxide, pcre2, glib and qt@5
==> Fetching cmake
==> Downloading https://ghcr.io/v2/homebrew/core/cmake/manifests/4.0.1
#################################################################################################################################################################################### 100.0%
==> Downloading https://ghcr.io/v2/homebrew/core/cmake/blobs/sha256:5fc195bfee6a1a218f792107dcf52da2f49c764dad521367ef8134e65bab442b
#################################################################################################################################################################################### 100.0%
==> Fetching icu4c@77
==> Downloading https://ghcr.io/v2/homebrew/core/icu4c/77/manifests/77.1
#################################################################################################################################################################################### 100.0%
==> Downloading https://ghcr.io/v2/homebrew/core/icu4c/77/blobs/sha256:19f6b5fef0cdf1dfc7f136ca103348ec8530ffdf8012273f6ee4a6159cdfaf75
#################################################################################################################################################################################### 100.0%
==> Fetching xz
==> Downloading https://ghcr.io/v2/homebrew/core/xz/manifests/5.8.1
#################################################################################################################################################################################### 100.0%
==> Downloading https://ghcr.io/v2/homebrew/core/xz/blobs/sha256:dcd7823f2624cbcd08f55c232097a79300c7d76ab5969004db1a4785c6c0cd87
#################################################################################################################################################################################### 100.0%
==> Fetching boost
==> Downloading https://ghcr.io/v2/homebrew/core/boost/manifests/1.88.0
#################################################################################################################################################################################### 100.0%
==> Downloading https://ghcr.io/v2/homebrew/core/boost/blobs/sha256:40110dc77bd85db9b7bfc5c23d1cbd58f8ef501ba355484419f9d11ccabaefc1
#################################################################################################################################################################################### 100.0%
==> Fetching python@3.13
==> Downloading https://ghcr.io/v2/homebrew/core/python/3.13/manifests/3.13.3-1
#################################################################################################################################################################################### 100.0%
==> Downloading https://ghcr.io/v2/homebrew/core/python/3.13/blobs/sha256:243ab8eec20fbc33c7d6760af6097842a400a9e67c07316cbc9b8de4c2762df7
#################################################################################################################################################################################### 100.0%
==> Fetching boost-python3
==> Downloading https://ghcr.io/v2/homebrew/core/boost-python3/manifests/1.88.0
#################################################################################################################################################################################### 100.0%
==> Downloading https://ghcr.io/v2/homebrew/core/boost-python3/blobs/sha256:c14fd4a92ecf59b0cd310d2b40ac374861acda10acc91bf22a60f561eef32327
#################################################################################################################################################################################### 100.0%
==> Fetching pkgconf
==> Downloading https://ghcr.io/v2/homebrew/core/pkgconf/manifests/2.4.3-1
#################################################################################################################################################################################### 100.0%
==> Downloading https://ghcr.io/v2/homebrew/core/pkgconf/blobs/sha256:3feba2e952500e4ab9261ac59a19e07c310d1147e31496f62b591e4b21b68683
#################################################################################################################################################################################### 100.0%
==> Fetching libusb
==> Downloading https://ghcr.io/v2/homebrew/core/libusb/manifests/1.0.28
#################################################################################################################################################################################### 100.0%
==> Downloading https://ghcr.io/v2/homebrew/core/libusb/blobs/sha256:fb9ed6ef1610e649e3b95f2eb2945f7329fc5695bcb2521c4dca924b61b3ff31
#################################################################################################################################################################################### 100.0%
==> Fetching twam/openfpga/icestorm
==> Downloading https://github.com/YosysHQ/icestorm/archive/738af822905fdcf0466e9dd784b9ae4b0b34987f.tar.gz
==> Downloading from https://codeload.github.com/YosysHQ/icestorm/tar.gz/738af822905fdcf0466e9dd784b9ae4b0b34987f
#-#O=- #      #                                                                                                                                                                            
==> Fetching libgit2
==> Downloading https://ghcr.io/v2/homebrew/core/libgit2/manifests/1.9.0
#################################################################################################################################################################################### 100.0%
==> Downloading https://ghcr.io/v2/homebrew/core/libgit2/blobs/sha256:f0ee705c27e87553582c58556a2a20a766af1e1ffbef0f1c676b0244e89398b9
#################################################################################################################################################################################### 100.0%
==> Fetching llvm@19
==> Downloading https://ghcr.io/v2/homebrew/core/llvm/19/manifests/19.1.7
#################################################################################################################################################################################### 100.0%
==> Downloading https://ghcr.io/v2/homebrew/core/llvm/19/blobs/sha256:7b14323528280fe8da37c282cfe3b5b34a9a56f0730c3ce599d165f2c5353a8a
#################################################################################################################################################################################### 100.0%
==> Fetching rust
==> Downloading https://ghcr.io/v2/homebrew/core/rust/manifests/1.86.0
#################################################################################################################################################################################### 100.0%
==> Downloading https://ghcr.io/v2/homebrew/core/rust/blobs/sha256:971ead27d588e6366d860f852475920761575de9d68638a649bdac997fc457c9
#################################################################################################################################################################################### 100.0%
==> Fetching twam/openfpga/prjoxide
==> Downloading https://github.com/gatecat/prjoxide-db/archive/56009be1ca77a7123ffdb50a813216302a42ac27.tar.gz
==> Downloading from https://codeload.github.com/gatecat/prjoxide-db/tar.gz/56009be1ca77a7123ffdb50a813216302a42ac27
#-#O=- #      #                                                                                                                                                                            
==> Downloading https://github.com/gatecat/prjoxide/archive/30712ff988a3ea7700fa11b87ae2d77e55c7c468.tar.gz
==> Downloading from https://codeload.github.com/gatecat/prjoxide/tar.gz/30712ff988a3ea7700fa11b87ae2d77e55c7c468
##O=-#     #                                                                                                                                                                               
==> Fetching pcre2
==> Downloading https://ghcr.io/v2/homebrew/core/pcre2/manifests/10.45
#################################################################################################################################################################################### 100.0%
==> Downloading https://ghcr.io/v2/homebrew/core/pcre2/blobs/sha256:f2abc87de6796a4e639f93d42c6d515cad90418fd7b701bcf322fb8e1443704e
#################################################################################################################################################################################### 100.0%
==> Fetching glib
==> Downloading https://ghcr.io/v2/homebrew/core/glib/manifests/2.84.1
#################################################################################################################################################################################### 100.0%
==> Downloading https://ghcr.io/v2/homebrew/core/glib/blobs/sha256:d9185ea25f133c7b2cb36185bb02b49ef98bb044045389d5bbfb9f9525170a0f
#################################################################################################################################################################################### 100.0%
==> Fetching qt@5
==> Downloading https://ghcr.io/v2/homebrew/core/qt/5/manifests/5.15.16_2
#################################################################################################################################################################################### 100.0%
==> Downloading https://ghcr.io/v2/homebrew/core/qt/5/blobs/sha256:a661d1f9b62c9fff165ace3821f3befeb65620166b63d8795301f132cc9aeb50
#################################################################################################################################################################################### 100.0%
==> Fetching twam/openfpga/nextpnr
==> Downloading https://github.com/YosysHQ/nextpnr/archive/9c2d96f86ed56b77c9c325041b67654f26308270.tar.gz
==> Downloading from https://codeload.github.com/YosysHQ/nextpnr/tar.gz/9c2d96f86ed56b77c9c325041b67654f26308270
   #-=O=#      #         #                                                                                                                                                                 
==> Installing nextpnr from twam/openfpga
==> Installing dependencies for twam/openfpga/nextpnr: cmake, icu4c@77, xz, boost, python@3.13, boost-python3, pkgconf, libusb, twam/openfpga/icestorm, libgit2, llvm@19, rust, twam/openfpga/prjoxide, pcre2, glib and qt@5
==> Installing twam/openfpga/nextpnr dependency: cmake
==> Downloading https://ghcr.io/v2/homebrew/core/cmake/manifests/4.0.1
Already downloaded: /Users/valiha/Library/Caches/Homebrew/downloads/1cd2e5b904fde0602b0dee345943375b244723a75893a195d23090826289cc37--cmake-4.0.1.bottle_manifest.json
==> Pouring cmake--4.0.1.arm64_sequoia.bottle.tar.gz
🍺  /opt/homebrew/Cellar/cmake/4.0.1: 3,870 files, 57.8MB
==> Installing twam/openfpga/nextpnr dependency: icu4c@77
==> Downloading https://ghcr.io/v2/homebrew/core/icu4c/77/manifests/77.1
Already downloaded: /Users/valiha/Library/Caches/Homebrew/downloads/35ec2c3adb94255ba47424a4334da9616d97e1ec6d59ed907b368535018bed0a--icu4c@77-77.1.bottle_manifest.json
==> Pouring icu4c@77--77.1.arm64_sequoia.bottle.tar.gz
🍺  /opt/homebrew/Cellar/icu4c@77/77.1: 277 files, 81.3MB
==> Installing twam/openfpga/nextpnr dependency: xz
==> Downloading https://ghcr.io/v2/homebrew/core/xz/manifests/5.8.1
Already downloaded: /Users/valiha/Library/Caches/Homebrew/downloads/86a115cc1d43ff8a480fd907f812e70a403e1675d8a7223f61bbb08cbd2adc27--xz-5.8.1.bottle_manifest.json
==> Pouring xz--5.8.1.arm64_sequoia.bottle.tar.gz
🍺  /opt/homebrew/Cellar/xz/5.8.1: 96 files, 2.5MB
==> Installing twam/openfpga/nextpnr dependency: boost
==> Downloading https://ghcr.io/v2/homebrew/core/boost/manifests/1.88.0
Already downloaded: /Users/valiha/Library/Caches/Homebrew/downloads/d1d650e10b72bb083df7414ad7171a3c5cf1d0d72a3e3773ec969dffbea19d9a--boost-1.88.0.bottle_manifest.json
==> Pouring boost--1.88.0.arm64_sequoia.bottle.tar.gz
🍺  /opt/homebrew/Cellar/boost/1.88.0: 16,266 files, 346.2MB
==> Installing twam/openfpga/nextpnr dependency: python@3.13
==> Downloading https://ghcr.io/v2/homebrew/core/python/3.13/manifests/3.13.3-1
Already downloaded: /Users/valiha/Library/Caches/Homebrew/downloads/c1320fdecb7ec29ab4a10c506bbe39179751a95489af3414b3a4acce32721cc0--python@3.13-3.13.3-1.bottle_manifest.json
==> Pouring python@3.13--3.13.3.arm64_sequoia.bottle.1.tar.gz
Warning: These files were overwritten during the `brew link` step:
/opt/homebrew/lib/python3.13/site-packages/pip/__init__.py
/opt/homebrew/lib/python3.13/site-packages/pip/__main__.py
/opt/homebrew/lib/python3.13/site-packages/pip/__pip-runner__.py
/opt/homebrew/lib/python3.13/site-packages/pip/_internal/__init__.py
/opt/homebrew/lib/python3.13/site-packages/pip/_internal/build_env.py
/opt/homebrew/lib/python3.13/site-packages/pip/_internal/cache.py
/opt/homebrew/lib/python3.13/site-packages/pip/_internal/cli/__init__.py
/opt/homebrew/lib/python3.13/site-packages/pip/_internal/cli/autocompletion.py
/opt/homebrew/lib/python3.13/site-packages/pip/_internal/cli/base_command.py
/opt/homebrew/lib/python3.13/site-packages/pip/_internal/cli/cmdoptions.py
/opt/homebrew/lib/python3.13/site-packages/pip/_internal/cli/command_context.py
/opt/homebrew/lib/python3.13/site-packages/pip/_internal/cli/index_command.py
/opt/homebrew/lib/python3.13/site-packages/pip/_internal/cli/main.py
/opt/homebrew/lib/python3.13/site-packages/pip/_internal/cli/main_parser.py
/opt/homebrew/lib/python3.13/site-packages/pip/_internal/cli/parser.py
/opt/homebrew/lib/python3.13/site-packages/pip/_internal/cli/progress_bars.py
/opt/homebrew/lib/python3.13/site-packages/pip/_internal/cli/req_command.py
/opt/homebrew/lib/python3.13/site-packages/pip/_internal/cli/spinners.py
/opt/homebrew/lib/python3.13/site-packages/pip/_internal/cli/status_codes.py
/opt/homebrew/lib/python3.13/site-packages/pip/_internal/commands/__init__.py
/opt/homebrew/lib/python3.13/site-packages/pip/_internal/commands/cache.py
/opt/homebrew/lib/python3.13/site-packages/pip/_internal/commands/check.py
/opt/homebrew/lib/python3.13/site-packages/pip/_internal/commands/completion.py
/opt/homebrew/lib/python3.13/site-packages/pip/_internal/commands/configuration.py
/opt/homebrew/lib/python3.13/site-packages/pip/_internal/commands/debug.py
/opt/homebrew/lib/python3.13/site-packages/pip/_internal/commands/download.py
/opt/homebrew/lib/python3.13/site-packages/pip/_internal/commands/freeze.py
/opt/homebrew/lib/python3.13/site-packages/pip/_internal/commands/hash.py
/opt/homebrew/lib/python3.13/site-packages/pip/_internal/commands/help.py
/opt/homebrew/lib/python3.13/site-packages/pip/_internal/commands/index.py
/opt/homebrew/lib/python3.13/site-packages/pip/_internal/commands/inspect.py
/opt/homebrew/lib/python3.13/site-packages/pip/_internal/commands/install.py
/opt/homebrew/lib/python3.13/site-packages/pip/_internal/commands/list.py
/opt/homebrew/lib/python3.13/site-packages/pip/_internal/commands/search.py
/opt/homebrew/lib/python3.13/site-packages/pip/_internal/commands/show.py
/opt/homebrew/lib/python3.13/site-packages/pip/_internal/commands/uninstall.py
/opt/homebrew/lib/python3.13/site-packages/pip/_internal/commands/wheel.py
/opt/homebrew/lib/python3.13/site-packages/pip/_internal/configuration.py
/opt/homebrew/lib/python3.13/site-packages/pip/_internal/distributions/__init__.py
/opt/homebrew/lib/python3.13/site-packages/pip/_internal/distributions/base.py
/opt/homebrew/lib/python3.13/site-packages/pip/_internal/distributions/installed.py
/opt/homebrew/lib/python3.13/site-packages/pip/_internal/distributions/sdist.py
/opt/homebrew/lib/python3.13/site-packages/pip/_internal/distributions/wheel.py
/opt/homebrew/lib/python3.13/site-packages/pip/_internal/exceptions.py
/opt/homebrew/lib/python3.13/site-packages/pip/_internal/index/__init__.py
/opt/homebrew/lib/python3.13/site-packages/pip/_internal/index/collector.py
/opt/homebrew/lib/python3.13/site-packages/pip/_internal/index/package_finder.py
/opt/homebrew/lib/python3.13/site-packages/pip/_internal/index/sources.py
/opt/homebrew/lib/python3.13/site-packages/pip/_internal/locations/__init__.py
/opt/homebrew/lib/python3.13/site-packages/pip/_internal/locations/_distutils.py
/opt/homebrew/lib/python3.13/site-packages/pip/_internal/locations/_sysconfig.py
/opt/homebrew/lib/python3.13/site-packages/pip/_internal/locations/base.py
/opt/homebrew/lib/python3.13/site-packages/pip/_internal/main.py
/opt/homebrew/lib/python3.13/site-packages/pip/_internal/metadata/__init__.py
/opt/homebrew/lib/python3.13/site-packages/pip/_internal/metadata/_json.py
/opt/homebrew/lib/python3.13/site-packages/pip/_internal/metadata/base.py
/opt/homebrew/lib/python3.13/site-packages/pip/_internal/metadata/importlib/__init__.py
/opt/homebrew/lib/python3.13/site-packages/pip/_internal/metadata/importlib/_compat.py
/opt/homebrew/lib/python3.13/site-packages/pip/_internal/metadata/importlib/_dists.py
/opt/homebrew/lib/python3.13/site-packages/pip/_internal/metadata/importlib/_envs.py
/opt/homebrew/lib/python3.13/site-packages/pip/_internal/metadata/pkg_resources.py
/opt/homebrew/lib/python3.13/site-packages/pip/_internal/models/__init__.py
/opt/homebrew/lib/python3.13/site-packages/pip/_internal/models/candidate.py
/opt/homebrew/lib/python3.13/site-packages/pip/_internal/models/direct_url.py
/opt/homebrew/lib/python3.13/site-packages/pip/_internal/models/format_control.py
/opt/homebrew/lib/python3.13/site-packages/pip/_internal/models/index.py
/opt/homebrew/lib/python3.13/site-packages/pip/_internal/models/installation_report.py
/opt/homebrew/lib/python3.13/site-packages/pip/_internal/models/link.py
/opt/homebrew/lib/python3.13/site-packages/pip/_internal/models/scheme.py
/opt/homebrew/lib/python3.13/site-packages/pip/_internal/models/search_scope.py
/opt/homebrew/lib/python3.13/site-packages/pip/_internal/models/selection_prefs.py
/opt/homebrew/lib/python3.13/site-packages/pip/_internal/models/target_python.py
/opt/homebrew/lib/python3.13/site-packages/pip/_internal/models/wheel.py
/opt/homebrew/lib/python3.13/site-packages/pip/_internal/network/__init__.py
/opt/homebrew/lib/python3.13/site-packages/pip/_internal/network/auth.py
/opt/homebrew/lib/python3.13/site-packages/pip/_internal/network/cache.py
/opt/homebrew/lib/python3.13/site-packages/pip/_internal/network/download.py
/opt/homebrew/lib/python3.13/site-packages/pip/_internal/network/lazy_wheel.py
/opt/homebrew/lib/python3.13/site-packages/pip/_internal/network/session.py
/opt/homebrew/lib/python3.13/site-packages/pip/_internal/network/utils.py
/opt/homebrew/lib/python3.13/site-packages/pip/_internal/network/xmlrpc.py
/opt/homebrew/lib/python3.13/site-packages/pip/_internal/operations/__init__.py
/opt/homebrew/lib/python3.13/site-packages/pip/_internal/operations/build/__init__.py
/opt/homebrew/lib/python3.13/site-packages/pip/_internal/operations/build/build_tracker.py
/opt/homebrew/lib/python3.13/site-packages/pip/_internal/operations/build/metadata.py
/opt/homebrew/lib/python3.13/site-packages/pip/_internal/operations/build/metadata_editable.py
/opt/homebrew/lib/python3.13/site-packages/pip/_internal/operations/build/metadata_legacy.py
/opt/homebrew/lib/python3.13/site-packages/pip/_internal/operations/build/wheel.py
/opt/homebrew/lib/python3.13/site-packages/pip/_internal/operations/build/wheel_editable.py
/opt/homebrew/lib/python3.13/site-packages/pip/_internal/operations/build/wheel_legacy.py
/opt/homebrew/lib/python3.13/site-packages/pip/_internal/operations/check.py
/opt/homebrew/lib/python3.13/site-packages/pip/_internal/operations/freeze.py
/opt/homebrew/lib/python3.13/site-packages/pip/_internal/operations/install/__init__.py
/opt/homebrew/lib/python3.13/site-packages/pip/_internal/operations/install/editable_legacy.py
/opt/homebrew/lib/python3.13/site-packages/pip/_internal/operations/install/wheel.py
/opt/homebrew/lib/python3.13/site-packages/pip/_internal/operations/prepare.py
/opt/homebrew/lib/python3.13/site-packages/pip/_internal/pyproject.py
/opt/homebrew/lib/python3.13/site-packages/pip/_internal/req/__init__.py
/opt/homebrew/lib/python3.13/site-packages/pip/_internal/req/constructors.py
/opt/homebrew/lib/python3.13/site-packages/pip/_internal/req/req_file.py
/opt/homebrew/lib/python3.13/site-packages/pip/_internal/req/req_install.py
/opt/homebrew/lib/python3.13/site-packages/pip/_internal/req/req_set.py
/opt/homebrew/lib/python3.13/site-packages/pip/_internal/req/req_uninstall.py
/opt/homebrew/lib/python3.13/site-packages/pip/_internal/resolution/__init__.py
/opt/homebrew/lib/python3.13/site-packages/pip/_internal/resolution/base.py
/opt/homebrew/lib/python3.13/site-packages/pip/_internal/resolution/legacy/__init__.py
/opt/homebrew/lib/python3.13/site-packages/pip/_internal/resolution/legacy/resolver.py
/opt/homebrew/lib/python3.13/site-packages/pip/_internal/resolution/resolvelib/__init__.py
/opt/homebrew/lib/python3.13/site-packages/pip/_internal/resolution/resolvelib/base.py
/opt/homebrew/lib/python3.13/site-packages/pip/_internal/resolution/resolvelib/candidates.py
/opt/homebrew/lib/python3.13/site-packages/pip/_internal/resolution/resolvelib/factory.py
/opt/homebrew/lib/python3.13/site-packages/pip/_internal/resolution/resolvelib/found_candidates.py
/opt/homebrew/lib/python3.13/site-packages/pip/_internal/resolution/resolvelib/provider.py
/opt/homebrew/lib/python3.13/site-packages/pip/_internal/resolution/resolvelib/reporter.py
/opt/homebrew/lib/python3.13/site-packages/pip/_internal/resolution/resolvelib/requirements.py
/opt/homebrew/lib/python3.13/site-packages/pip/_internal/resolution/resolvelib/resolver.py
/opt/homebrew/lib/python3.13/site-packages/pip/_internal/self_outdated_check.py
/opt/homebrew/lib/python3.13/site-packages/pip/_internal/utils/__init__.py
/opt/homebrew/lib/python3.13/site-packages/pip/_internal/utils/_jaraco_text.py
/opt/homebrew/lib/python3.13/site-packages/pip/_internal/utils/_log.py
/opt/homebrew/lib/python3.13/site-packages/pip/_internal/utils/appdirs.py
/opt/homebrew/lib/python3.13/site-packages/pip/_internal/utils/compat.py
/opt/homebrew/lib/python3.13/site-packages/pip/_internal/utils/compatibility_tags.py
/opt/homebrew/lib/python3.13/site-packages/pip/_internal/utils/datetime.py
/opt/homebrew/lib/python3.13/site-packages/pip/_internal/utils/deprecation.py
/opt/homebrew/lib/python3.13/site-packages/pip/_internal/utils/direct_url_helpers.py
/opt/homebrew/lib/python3.13/site-packages/pip/_internal/utils/egg_link.py
/opt/homebrew/lib/python3.13/site-packages/pip/_internal/utils/entrypoints.py
/opt/homebrew/lib/python3.13/site-packages/pip/_internal/utils/filesystem.py
/opt/homebrew/lib/python3.13/site-packages/pip/_internal/utils/filetypes.py
/opt/homebrew/lib/python3.13/site-packages/pip/_internal/utils/glibc.py
/opt/homebrew/lib/python3.13/site-packages/pip/_internal/utils/hashes.py
/opt/homebrew/lib/python3.13/site-packages/pip/_internal/utils/logging.py
/opt/homebrew/lib/python3.13/site-packages/pip/_internal/utils/misc.py
/opt/homebrew/lib/python3.13/site-packages/pip/_internal/utils/packaging.py
/opt/homebrew/lib/python3.13/site-packages/pip/_internal/utils/retry.py
/opt/homebrew/lib/python3.13/site-packages/pip/_internal/utils/setuptools_build.py
/opt/homebrew/lib/python3.13/site-packages/pip/_internal/utils/subprocess.py
/opt/homebrew/lib/python3.13/site-packages/pip/_internal/utils/temp_dir.py
/opt/homebrew/lib/python3.13/site-packages/pip/_internal/utils/unpacking.py
/opt/homebrew/lib/python3.13/site-packages/pip/_internal/utils/urls.py
/opt/homebrew/lib/python3.13/site-packages/pip/_internal/utils/virtualenv.py
/opt/homebrew/lib/python3.13/site-packages/pip/_internal/utils/wheel.py
/opt/homebrew/lib/python3.13/site-packages/pip/_internal/vcs/__init__.py
/opt/homebrew/lib/python3.13/site-packages/pip/_internal/vcs/bazaar.py
/opt/homebrew/lib/python3.13/site-packages/pip/_internal/vcs/git.py
/opt/homebrew/lib/python3.13/site-packages/pip/_internal/vcs/mercurial.py
/opt/homebrew/lib/python3.13/site-packages/pip/_internal/vcs/subversion.py
/opt/homebrew/lib/python3.13/site-packages/pip/_internal/vcs/versioncontrol.py
/opt/homebrew/lib/python3.13/site-packages/pip/_internal/wheel_builder.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/__init__.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/cachecontrol/__init__.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/cachecontrol/_cmd.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/cachecontrol/adapter.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/cachecontrol/cache.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/cachecontrol/caches/__init__.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/cachecontrol/caches/file_cache.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/cachecontrol/caches/redis_cache.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/cachecontrol/controller.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/cachecontrol/filewrapper.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/cachecontrol/heuristics.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/cachecontrol/py.typed
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/cachecontrol/serialize.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/cachecontrol/wrapper.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/certifi/__init__.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/certifi/__main__.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/certifi/cacert.pem
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/certifi/core.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/certifi/py.typed
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/distlib/__init__.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/distlib/compat.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/distlib/database.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/distlib/index.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/distlib/locators.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/distlib/manifest.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/distlib/markers.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/distlib/metadata.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/distlib/resources.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/distlib/scripts.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/distlib/t32.exe
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/distlib/t64-arm.exe
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/distlib/t64.exe
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/distlib/util.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/distlib/version.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/distlib/w32.exe
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/distlib/w64-arm.exe
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/distlib/w64.exe
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/distlib/wheel.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/distro/__init__.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/distro/__main__.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/distro/distro.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/distro/py.typed
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/idna/__init__.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/idna/codec.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/idna/compat.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/idna/core.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/idna/idnadata.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/idna/intranges.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/idna/package_data.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/idna/py.typed
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/idna/uts46data.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/msgpack/__init__.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/msgpack/exceptions.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/msgpack/ext.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/msgpack/fallback.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/packaging/__init__.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/packaging/_elffile.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/packaging/_manylinux.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/packaging/_musllinux.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/packaging/_parser.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/packaging/_structures.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/packaging/_tokenizer.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/packaging/licenses/__init__.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/packaging/licenses/_spdx.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/packaging/markers.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/packaging/metadata.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/packaging/py.typed
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/packaging/requirements.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/packaging/specifiers.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/packaging/tags.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/packaging/utils.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/packaging/version.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/pkg_resources/__init__.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/platformdirs/__init__.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/platformdirs/__main__.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/platformdirs/android.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/platformdirs/api.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/platformdirs/macos.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/platformdirs/py.typed
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/platformdirs/unix.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/platformdirs/version.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/platformdirs/windows.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/pygments/__init__.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/pygments/__main__.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/pygments/cmdline.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/pygments/console.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/pygments/filter.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/pygments/filters/__init__.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/pygments/formatter.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/pygments/formatters/__init__.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/pygments/formatters/_mapping.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/pygments/formatters/bbcode.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/pygments/formatters/groff.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/pygments/formatters/html.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/pygments/formatters/img.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/pygments/formatters/irc.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/pygments/formatters/latex.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/pygments/formatters/other.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/pygments/formatters/pangomarkup.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/pygments/formatters/rtf.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/pygments/formatters/svg.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/pygments/formatters/terminal.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/pygments/formatters/terminal256.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/pygments/lexer.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/pygments/lexers/__init__.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/pygments/lexers/_mapping.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/pygments/lexers/python.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/pygments/modeline.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/pygments/plugin.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/pygments/regexopt.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/pygments/scanner.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/pygments/sphinxext.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/pygments/style.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/pygments/styles/__init__.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/pygments/styles/_mapping.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/pygments/token.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/pygments/unistring.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/pygments/util.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/pyproject_hooks/__init__.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/pyproject_hooks/_impl.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/pyproject_hooks/_in_process/__init__.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/pyproject_hooks/_in_process/_in_process.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/pyproject_hooks/py.typed
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/requests/__init__.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/requests/__version__.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/requests/_internal_utils.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/requests/adapters.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/requests/api.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/requests/auth.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/requests/certs.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/requests/compat.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/requests/cookies.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/requests/exceptions.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/requests/help.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/requests/hooks.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/requests/models.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/requests/packages.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/requests/sessions.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/requests/status_codes.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/requests/structures.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/requests/utils.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/resolvelib/__init__.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/resolvelib/compat/__init__.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/resolvelib/compat/collections_abc.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/resolvelib/providers.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/resolvelib/py.typed
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/resolvelib/reporters.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/resolvelib/resolvers.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/resolvelib/structs.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/rich/__init__.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/rich/__main__.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/rich/_cell_widths.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/rich/_emoji_codes.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/rich/_emoji_replace.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/rich/_export_format.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/rich/_extension.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/rich/_fileno.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/rich/_inspect.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/rich/_log_render.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/rich/_loop.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/rich/_null_file.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/rich/_palettes.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/rich/_pick.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/rich/_ratio.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/rich/_spinners.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/rich/_stack.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/rich/_timer.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/rich/_win32_console.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/rich/_windows.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/rich/_windows_renderer.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/rich/_wrap.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/rich/abc.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/rich/align.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/rich/ansi.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/rich/bar.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/rich/box.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/rich/cells.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/rich/color.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/rich/color_triplet.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/rich/columns.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/rich/console.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/rich/constrain.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/rich/containers.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/rich/control.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/rich/default_styles.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/rich/diagnose.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/rich/emoji.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/rich/errors.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/rich/file_proxy.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/rich/filesize.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/rich/highlighter.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/rich/json.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/rich/jupyter.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/rich/layout.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/rich/live.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/rich/live_render.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/rich/logging.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/rich/markup.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/rich/measure.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/rich/padding.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/rich/pager.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/rich/palette.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/rich/panel.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/rich/pretty.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/rich/progress.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/rich/progress_bar.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/rich/prompt.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/rich/protocol.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/rich/py.typed
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/rich/region.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/rich/repr.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/rich/rule.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/rich/scope.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/rich/screen.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/rich/segment.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/rich/spinner.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/rich/status.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/rich/style.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/rich/styled.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/rich/syntax.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/rich/table.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/rich/terminal_theme.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/rich/text.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/rich/theme.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/rich/themes.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/rich/traceback.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/rich/tree.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/tomli/__init__.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/tomli/_parser.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/tomli/_re.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/tomli/_types.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/tomli/py.typed
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/truststore/__init__.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/truststore/_api.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/truststore/_macos.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/truststore/_openssl.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/truststore/_ssl_constants.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/truststore/_windows.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/truststore/py.typed
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/typing_extensions.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/urllib3/__init__.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/urllib3/_collections.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/urllib3/_version.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/urllib3/connection.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/urllib3/connectionpool.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/urllib3/contrib/__init__.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/urllib3/contrib/_appengine_environ.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/urllib3/contrib/_securetransport/__init__.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/urllib3/contrib/_securetransport/bindings.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/urllib3/contrib/_securetransport/low_level.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/urllib3/contrib/appengine.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/urllib3/contrib/ntlmpool.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/urllib3/contrib/pyopenssl.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/urllib3/contrib/securetransport.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/urllib3/contrib/socks.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/urllib3/exceptions.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/urllib3/fields.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/urllib3/filepost.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/urllib3/packages/__init__.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/urllib3/packages/backports/__init__.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/urllib3/packages/backports/makefile.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/urllib3/packages/backports/weakref_finalize.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/urllib3/packages/six.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/urllib3/poolmanager.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/urllib3/request.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/urllib3/response.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/urllib3/util/__init__.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/urllib3/util/connection.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/urllib3/util/proxy.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/urllib3/util/queue.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/urllib3/util/request.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/urllib3/util/response.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/urllib3/util/retry.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/urllib3/util/ssl_.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/urllib3/util/ssl_match_hostname.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/urllib3/util/ssltransport.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/urllib3/util/timeout.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/urllib3/util/url.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/urllib3/util/wait.py
/opt/homebrew/lib/python3.13/site-packages/pip/_vendor/vendor.txt
/opt/homebrew/lib/python3.13/site-packages/pip/py.typed
/opt/homebrew/lib/python3.13/site-packages/wheel/__init__.py
/opt/homebrew/lib/python3.13/site-packages/wheel/__main__.py
/opt/homebrew/lib/python3.13/site-packages/wheel/_bdist_wheel.py
/opt/homebrew/lib/python3.13/site-packages/wheel/_setuptools_logging.py
/opt/homebrew/lib/python3.13/site-packages/wheel/bdist_wheel.py
/opt/homebrew/lib/python3.13/site-packages/wheel/cli/__init__.py
/opt/homebrew/lib/python3.13/site-packages/wheel/cli/convert.py
/opt/homebrew/lib/python3.13/site-packages/wheel/cli/pack.py
/opt/homebrew/lib/python3.13/site-packages/wheel/cli/tags.py
/opt/homebrew/lib/python3.13/site-packages/wheel/cli/unpack.py
/opt/homebrew/lib/python3.13/site-packages/wheel/macosx_libfile.py
/opt/homebrew/lib/python3.13/site-packages/wheel/metadata.py
/opt/homebrew/lib/python3.13/site-packages/wheel/util.py
/opt/homebrew/lib/python3.13/site-packages/wheel/vendored/__init__.py
/opt/homebrew/lib/python3.13/site-packages/wheel/vendored/packaging/LICENSE
/opt/homebrew/lib/python3.13/site-packages/wheel/vendored/packaging/LICENSE.APACHE
/opt/homebrew/lib/python3.13/site-packages/wheel/vendored/packaging/LICENSE.BSD
/opt/homebrew/lib/python3.13/site-packages/wheel/vendored/packaging/__init__.py
/opt/homebrew/lib/python3.13/site-packages/wheel/vendored/packaging/_elffile.py
/opt/homebrew/lib/python3.13/site-packages/wheel/vendored/packaging/_manylinux.py
/opt/homebrew/lib/python3.13/site-packages/wheel/vendored/packaging/_musllinux.py
/opt/homebrew/lib/python3.13/site-packages/wheel/vendored/packaging/_parser.py
/opt/homebrew/lib/python3.13/site-packages/wheel/vendored/packaging/_structures.py
/opt/homebrew/lib/python3.13/site-packages/wheel/vendored/packaging/_tokenizer.py
/opt/homebrew/lib/python3.13/site-packages/wheel/vendored/packaging/markers.py
/opt/homebrew/lib/python3.13/site-packages/wheel/vendored/packaging/requirements.py
/opt/homebrew/lib/python3.13/site-packages/wheel/vendored/packaging/specifiers.py
/opt/homebrew/lib/python3.13/site-packages/wheel/vendored/packaging/tags.py
/opt/homebrew/lib/python3.13/site-packages/wheel/vendored/packaging/utils.py
/opt/homebrew/lib/python3.13/site-packages/wheel/vendored/packaging/version.py
/opt/homebrew/lib/python3.13/site-packages/wheel/vendored/vendor.txt
/opt/homebrew/lib/python3.13/site-packages/wheel/wheelfile.py
/opt/homebrew/lib/python3.13/site-packages/wheel-0.45.1.dist-info/INSTALLER
/opt/homebrew/lib/python3.13/site-packages/wheel-0.45.1.dist-info/METADATA
/opt/homebrew/lib/python3.13/site-packages/wheel-0.45.1.dist-info/REQUESTED
/opt/homebrew/lib/python3.13/site-packages/wheel-0.45.1.dist-info/WHEEL
/opt/homebrew/lib/python3.13/site-packages/wheel-0.45.1.dist-info/entry_points.txt

They have been backed up to: /Users/valiha/Library/Caches/Homebrew/Backup
==> Summary
🍺  /opt/homebrew/Cellar/python@3.13/3.13.3: 3,598 files, 66.7MB
==> Installing twam/openfpga/nextpnr dependency: boost-python3
==> Downloading https://ghcr.io/v2/homebrew/core/boost-python3/manifests/1.88.0
Already downloaded: /Users/valiha/Library/Caches/Homebrew/downloads/d55aa54efd2947daec08556195107f8799ce8f865d00bfe7b7960997364ea57c--boost-python3-1.88.0.bottle_manifest.json
==> Pouring boost-python3--1.88.0.arm64_sequoia.bottle.tar.gz
🍺  /opt/homebrew/Cellar/boost-python3/1.88.0: 16 files, 7.4MB
==> Installing twam/openfpga/nextpnr dependency: pkgconf
==> Downloading https://ghcr.io/v2/homebrew/core/pkgconf/manifests/2.4.3-1
Already downloaded: /Users/valiha/Library/Caches/Homebrew/downloads/f938254e85413ef0d18283c9c932823434b88c0c790e04e7534e2a3e923d0588--pkgconf-2.4.3-1.bottle_manifest.json
==> Pouring pkgconf--2.4.3.arm64_sequoia.bottle.1.tar.gz
🍺  /opt/homebrew/Cellar/pkgconf/2.4.3: 27 files, 487.5KB
==> Installing twam/openfpga/nextpnr dependency: libusb
==> Downloading https://ghcr.io/v2/homebrew/core/libusb/manifests/1.0.28
Already downloaded: /Users/valiha/Library/Caches/Homebrew/downloads/e0f27c147ac7d4b46b47319bf996fc7ce512af2095604632112d4e9bd085d102--libusb-1.0.28.bottle_manifest.json
==> Pouring libusb--1.0.28.arm64_sequoia.bottle.tar.gz
🍺  /opt/homebrew/Cellar/libusb/1.0.28: 23 files, 629KB
==> Installing twam/openfpga/nextpnr dependency: twam/openfpga/icestorm
==> make install PREFIX=/opt/homebrew/Cellar/icestorm/20240624 PRETTY=0
🍺  /opt/homebrew/Cellar/icestorm/20240624: 37 files, 109.9MB, built in 25 seconds
==> Installing twam/openfpga/nextpnr dependency: libgit2
==> Downloading https://ghcr.io/v2/homebrew/core/libgit2/manifests/1.9.0
Already downloaded: /Users/valiha/Library/Caches/Homebrew/downloads/42775fae97faa88bd981a6dc6a0093c433220ca8b48e0b02cfcb8d665a9672c8--libgit2-1.9.0.bottle_manifest.json
==> Pouring libgit2--1.9.0.arm64_sequoia.bottle.tar.gz
🍺  /opt/homebrew/Cellar/libgit2/1.9.0: 109 files, 4.9MB
==> Installing twam/openfpga/nextpnr dependency: llvm@19
==> Downloading https://ghcr.io/v2/homebrew/core/llvm/19/manifests/19.1.7
Already downloaded: /Users/valiha/Library/Caches/Homebrew/downloads/52a0bb96d79f4a71e7151869f48e5eed0a83bdef0de133ca4ae96dc0ac3df837--llvm@19-19.1.7.bottle_manifest.json
==> Pouring llvm@19--19.1.7.arm64_sequoia.bottle.tar.gz
🍺  /opt/homebrew/Cellar/llvm@19/19.1.7: 7,514 files, 1.7GB
==> Installing twam/openfpga/nextpnr dependency: rust
==> Downloading https://ghcr.io/v2/homebrew/core/rust/manifests/1.86.0
Already downloaded: /Users/valiha/Library/Caches/Homebrew/downloads/5e0616244331af16419b56126b56409f006d450d66005d85663e5f8b71c5fb54--rust-1.86.0.bottle_manifest.json
==> Pouring rust--1.86.0.arm64_sequoia.bottle.tar.gz
🍺  /opt/homebrew/Cellar/rust/1.86.0: 3,648 files, 322.5MB
==> Installing twam/openfpga/nextpnr dependency: twam/openfpga/prjoxide
==> cargo install
🍺  /opt/homebrew/Cellar/prjoxide/20240105: 8 files, 20.0MB, built in 20 seconds
==> Installing twam/openfpga/nextpnr dependency: pcre2
==> Downloading https://ghcr.io/v2/homebrew/core/pcre2/manifests/10.45
Already downloaded: /Users/valiha/Library/Caches/Homebrew/downloads/bbac938545583185faba88567f1a952d7cc0b825820a2980533f7b3550dc31ad--pcre2-10.45.bottle_manifest.json
==> Pouring pcre2--10.45.arm64_sequoia.bottle.tar.gz
🍺  /opt/homebrew/Cellar/pcre2/10.45: 242 files, 6.7MB
==> Installing twam/openfpga/nextpnr dependency: glib
==> Downloading https://ghcr.io/v2/homebrew/core/glib/manifests/2.84.1
Already downloaded: /Users/valiha/Library/Caches/Homebrew/downloads/b504bc646f90477618e8d0155f248b1b09da807ecd327effefeab059e7a454d6--glib-2.84.1.bottle_manifest.json
==> Pouring glib--2.84.1.arm64_sequoia.bottle.tar.gz
🍺  /opt/homebrew/Cellar/glib/2.84.1: 504 files, 36.6MB
==> Installing twam/openfpga/nextpnr dependency: qt@5
==> Downloading https://ghcr.io/v2/homebrew/core/qt/5/manifests/5.15.16_2
Already downloaded: /Users/valiha/Library/Caches/Homebrew/downloads/5723cfabc0a0f0cdd36cd4b59d3d0e1cef611d1620ac13ed895c957d2ba5103e--qt@5-5.15.16_2.bottle_manifest.json
==> Pouring qt@5--5.15.16_2.arm64_sequoia.bottle.tar.gz
🍺  /opt/homebrew/Cellar/qt@5/5.15.16_2: 10,849 files, 341.7MB
==> Installing twam/openfpga/nextpnr --with-gui --without-arch-ecp5
==> cmake -DBUILD_GUI=ON -DSERIALIZE_CHIPDBS=FALSE -DICESTORM_INSTALL_PREFIX=/opt/homebrew/opt/icestorm -DOXIDE_INSTALL_PREFIX=/opt/homebrew/opt/prjoxide -DARCH=ice40;nexus -DCURRENT_GIT_
==> ninja
==> ninja install
🍺  /opt/homebrew/Cellar/nextpnr/20241022: 7 files, 257.7MB, built in 1 minute 39 seconds
==> Running `brew cleanup nextpnr`...
Disable this behaviour by setting HOMEBREW_NO_INSTALL_CLEANUP.
Hide these hints with HOMEBREW_NO_ENV_HINTS (see `man brew`).
==> Upgrading 50 dependents of upgraded formulae:
Disable this behaviour by setting HOMEBREW_NO_INSTALLED_DEPENDENTS_CHECK.
Hide these hints with HOMEBREW_NO_ENV_HINTS (see `man brew`).
aom 3.12.0 -> 3.12.1, at-spi2-core 2.54.1 -> 2.56.1, azure-cli 2.70.0 -> 2.71.0, cairo 1.18.2 -> 1.18.4, ccache 4.10.2_3 -> 4.11.2, curl 8.11.0_1 -> 8.13.0, gdk-pixbuf 2.42.12 -> 2.42.12_1, gnuplot 6.0.2 -> 6.0.2_1, gobject-introspection 1.82.0 -> 1.84.0, gpgme 1.24.1 -> 1.24.2, gsettings-desktop-schemas 47.1 -> 48.0, harfbuzz 10.4.0 -> 11.1.0, gtk-mac-integration 3.0.1_1 -> 3.0.2, jpeg-xl 0.11.1 -> 0.11.1_1, libarchive 3.7.7 -> 3.7.9, ffmpeg 7.1.1 -> 7.1.1_2, ghostscript 10.04.0 -> 10.05.0_1, imagemagick 7.1.1-44 -> 7.1.1-47, libavif 1.2.0 -> 1.2.1, libraw 0.21.3 -> 0.21.4, librsvg 2.59.2 -> 2.60.0, adwaita-icon-theme 47.0 -> 48.0, libvirt 11.1.0 -> 11.2.0, llvm 19.1.7_1 -> 20.1.3, locust 2.33.0 -> 2.36.2, meson 1.6.0 -> 1.7.2, netpbm 11.02.12 -> 11.02.15, numpy 2.2.3 -> 2.2.5, gnuradio 3.10.12.0 -> 3.10.12.0_1, openfpgaloader 0.12.1 -> 0.13.1, openjdk 23.0.1 -> 23.0.2, pango 1.56.1 -> 1.56.3, poppler 25.02.0 -> 25.04.0, py3cairo 1.27.0_1 -> 1.28.0, pyenv 2.4.22 -> 2.5.5, pygobject3 3.50.0_1 -> 3.52.3, pyqt 6.8.1 -> 6.9.0, python-argcomplete 3.5.3 -> 3.6.2, python@3.10 3.10.15 -> 3.10.17, python@3.11 3.11.10 -> 3.11.12, python@3.12 3.12.9 -> 3.12.10, qemu 9.2.2 -> 10.0.0, qt 6.8.2 -> 6.9.0, suite-sparse 7.8.3 -> 7.10.2, sundials 7.2.1 -> 7.3.0, tesseract 5.5.0 -> 5.5.0_1, texlive 20240312_3 -> 20250308_1, uhd 4.8.0.0 -> 4.8.0.0_1, wireshark 4.4.5 -> 4.4.6, yt-dlp 2024.11.4 -> 2025.3.31
==> Downloading https://ghcr.io/v2/homebrew/core/cairo/manifests/1.18.4
#################################################################################################################################################################################### 100.0%
==> Downloading https://ghcr.io/v2/homebrew/core/harfbuzz/manifests/11.1.0
#################################################################################################################################################################################### 100.0%
==> Fetching dependencies for harfbuzz: libx11 and cairo
==> Downloading https://ghcr.io/v2/homebrew/core/libx11/manifests/1.8.12
#################################################################################################################################################################################### 100.0%
==> Fetching libx11
==> Downloading https://ghcr.io/v2/homebrew/core/libx11/blobs/sha256:57ccd55767fd6ffc7d32940d1c59d59b42c82abff4abf795b4ca0df489da42f1
#################################################################################################################################################################################### 100.0%
==> Downloading https://ghcr.io/v2/homebrew/core/cairo/manifests/1.18.4
Already downloaded: /Users/valiha/Library/Caches/Homebrew/downloads/795ef2e2e2a57e6baba0fc9ceedb58980e8ec718aba0170b9441a0b25442cfbf--cairo-1.18.4.bottle_manifest.json
==> Fetching cairo
==> Downloading https://ghcr.io/v2/homebrew/core/cairo/blobs/sha256:6b2d148a34a670430a459c374376ebed890b61eb7573e8aa952a4b909f443cee
#################################################################################################################################################################################### 100.0%
==> Fetching harfbuzz
==> Downloading https://ghcr.io/v2/homebrew/core/harfbuzz/blobs/sha256:02ebf18df75fa41c143ce55ba0685681c76ec0dbc2d687a2b6ea097fcc69eaa6
#################################################################################################################################################################################### 100.0%
==> Downloading https://ghcr.io/v2/homebrew/core/openjdk/manifests/23.0.2
Already downloaded: /Users/valiha/Library/Caches/Homebrew/downloads/8dea1e6c16fdb5358c4865d24639ab139310acfcd2a8472a89f458bbb046eac5--openjdk-23.0.2.bottle_manifest.json
==> Downloading https://ghcr.io/v2/homebrew/core/curl/manifests/8.13.0-1
#################################################################################################################################################################################### 100.0%
==> Downloading https://ghcr.io/v2/homebrew/core/libarchive/manifests/3.7.9
#################################################################################################################################################################################### 100.0%
==> Downloading https://ghcr.io/v2/homebrew/core/llvm/manifests/20.1.3
#################################################################################################################################################################################### 100.0%
==> Fetching dependencies for llvm: z3
==> Downloading https://ghcr.io/v2/homebrew/core/z3/manifests/4.14.1
#################################################################################################################################################################################### 100.0%
==> Fetching z3
==> Downloading https://ghcr.io/v2/homebrew/core/z3/blobs/sha256:0090d3a9aac7fbbbb0734cdb24c0a8f891d99b97bc5e527ecf6db407cb17b4d2
#################################################################################################################################################################################### 100.0%
==> Fetching llvm
==> Downloading https://ghcr.io/v2/homebrew/core/llvm/blobs/sha256:50f7157b1fc8f75de33f0132a7a048fa02c4ff359d8157d06d4be60bec1e911e
#################################################################################################################################################################################### 100.0%
==> Downloading https://ghcr.io/v2/homebrew/core/ccache/manifests/4.11.2
#################################################################################################################################################################################### 100.0%
==> Fetching dependencies for ccache: blake3, fmt and xxhash
==> Downloading https://ghcr.io/v2/homebrew/core/blake3/manifests/1.8.2
#################################################################################################################################################################################### 100.0%
==> Fetching blake3
==> Downloading https://ghcr.io/v2/homebrew/core/blake3/blobs/sha256:601904a1b1f08581bc60847875b444ccd2c23f11aa68acb8d635ae57fb104304
#################################################################################################################################################################################### 100.0%
==> Downloading https://ghcr.io/v2/homebrew/core/fmt/manifests/11.1.4
#################################################################################################################################################################################### 100.0%
==> Fetching fmt
==> Downloading https://ghcr.io/v2/homebrew/core/fmt/blobs/sha256:a66ba523ff4d827b679de7e9ed284a1f3fc091c06152c64946e4c536f284d8c0
#################################################################################################################################################################################### 100.0%
==> Downloading https://ghcr.io/v2/homebrew/core/xxhash/manifests/0.8.3
#################################################################################################################################################################################### 100.0%
==> Fetching xxhash
==> Downloading https://ghcr.io/v2/homebrew/core/xxhash/blobs/sha256:89bd0369c7033c364428cf03daad6f58ca5e5defd8dc585b8f0bc6a111714013
#################################################################################################################################################################################### 100.0%
==> Fetching ccache
==> Downloading https://ghcr.io/v2/homebrew/core/ccache/blobs/sha256:fecd42feb7f8fb4939cf74ec1f45dc4efda5a82f23528acf85f652cbbacd1145
#################################################################################################################################################################################### 100.0%
==> Downloading https://ghcr.io/v2/homebrew/core/gdk-pixbuf/manifests/2.42.12_1
#################################################################################################################################################################################### 100.0%
==> Downloading https://ghcr.io/v2/homebrew/core/jpeg-xl/manifests/0.11.1_1
#################################################################################################################################################################################### 100.0%
==> Fetching dependencies for jpeg-xl: openexr
==> Downloading https://ghcr.io/v2/homebrew/core/openexr/manifests/3.3.3
#################################################################################################################################################################################### 100.0%
==> Fetching openexr
==> Downloading https://ghcr.io/v2/homebrew/core/openexr/blobs/sha256:095b03c2de45fa33ca35a42af614570d627a9a804dc99dc1c207b4687437c4b6
#################################################################################################################################################################################### 100.0%
==> Fetching jpeg-xl
==> Downloading https://ghcr.io/v2/homebrew/core/jpeg-xl/blobs/sha256:c3aceba825400a7d64dbd95d622ce59f0414e54cdedb792afc51d9278dae65b6
#################################################################################################################################################################################### 100.0%
==> Downloading https://ghcr.io/v2/homebrew/core/aom/manifests/3.12.1
#################################################################################################################################################################################### 100.0%
==> Fetching aom
==> Downloading https://ghcr.io/v2/homebrew/core/aom/blobs/sha256:7187a5accf9da7614d96b6fb07df1c0b144cfb096d920e9936fa78b6fba18c4a
#################################################################################################################################################################################### 100.0%
==> Downloading https://ghcr.io/v2/homebrew/core/libavif/manifests/1.2.1
#################################################################################################################################################################################### 100.0%
==> Downloading https://ghcr.io/v2/homebrew/core/pango/manifests/1.56.3
#################################################################################################################################################################################### 100.0%
==> Fetching pango
==> Downloading https://ghcr.io/v2/homebrew/core/pango/blobs/sha256:39c8338524e71bf6019b72a2bbebebc78c6935dfad75a76db43ff9a8815bfe6b
#################################################################################################################################################################################### 100.0%
==> Downloading https://ghcr.io/v2/homebrew/core/qt/manifests/6.9.0
#################################################################################################################################################################################### 100.0%
==> Fetching dependencies for qt: dbus, double-conversion and jasper
==> Downloading https://ghcr.io/v2/homebrew/core/dbus/manifests/1.16.2
#################################################################################################################################################################################### 100.0%
==> Fetching dbus
==> Downloading https://ghcr.io/v2/homebrew/core/dbus/blobs/sha256:b03c304cbecc18a7fd132a24aac4ae0245a731b72ea7ce819353397cd0e05b2c
#################################################################################################################################################################################### 100.0%
==> Downloading https://ghcr.io/v2/homebrew/core/double-conversion/manifests/3.3.1
#################################################################################################################################################################################### 100.0%
==> Fetching double-conversion
==> Downloading https://ghcr.io/v2/homebrew/core/double-conversion/blobs/sha256:e45a082cb2703fa9054e6399e96aee5104cbeb25ce5e30799af503585e2015d4
#################################################################################################################################################################################### 100.0%
==> Downloading https://ghcr.io/v2/homebrew/core/jasper/manifests/4.2.5
#################################################################################################################################################################################### 100.0%
==> Fetching jasper
==> Downloading https://ghcr.io/v2/homebrew/core/jasper/blobs/sha256:5bf7fb8303c35cca02e48faa33254cc9d65306985bd4186d8141dc61bf3b643f
#################################################################################################################################################################################### 100.0%
==> Fetching qt
==> Downloading https://ghcr.io/v2/homebrew/core/qt/blobs/sha256:861acfe809369d19c8cbc923afa94c62f48784f087a150e09d3522e5eeb15f9e
#################################################################################################################################################################################### 100.0%
==> Downloading https://ghcr.io/v2/homebrew/core/gnuplot/manifests/6.0.2_1
#################################################################################################################################################################################### 100.0%
==> Fetching dependencies for gnuplot: libavif and libcerf
==> Downloading https://ghcr.io/v2/homebrew/core/libavif/manifests/1.2.1
Already downloaded: /Users/valiha/Library/Caches/Homebrew/downloads/a3880a25438e74c798bd1fc9305af44be3f3680e04c511626de04a030cf1838d--libavif-1.2.1.bottle_manifest.json
==> Fetching libavif
==> Downloading https://ghcr.io/v2/homebrew/core/libavif/blobs/sha256:5c44c28b7141328d5a3eca015fa7ac4fc13ecf42f137405358f658646264c766
#################################################################################################################################################################################### 100.0%
==> Downloading https://ghcr.io/v2/homebrew/core/libcerf/manifests/3.0
#################################################################################################################################################################################### 100.0%
==> Fetching libcerf
==> Downloading https://ghcr.io/v2/homebrew/core/libcerf/blobs/sha256:093e9b7e5a294c1064d174f62b4a17e09bfb57f0fe2dd97b8b6091cf9e6d4ff6
#################################################################################################################################################################################### 100.0%
==> Fetching gnuplot
==> Downloading https://ghcr.io/v2/homebrew/core/gnuplot/blobs/sha256:f4614510eee98277e8f6707ede38ff75808199d9142b01b9b5d866c6b04e5e64
#################################################################################################################################################################################### 100.0%
==> Downloading https://ghcr.io/v2/homebrew/core/gobject-introspection/manifests/1.84.0
#################################################################################################################################################################################### 100.0%
==> Fetching gobject-introspection
==> Downloading https://ghcr.io/v2/homebrew/core/gobject-introspection/blobs/sha256:1940c1701f91ae5e7ef183e793b97be639d16e0f280d3732cecefb77bfd548f9
#################################################################################################################################################################################### 100.0%
==> Downloading https://ghcr.io/v2/homebrew/core/gpgme/manifests/1.24.2
Already downloaded: /Users/valiha/Library/Caches/Homebrew/downloads/b27e679213b6f16659cc6b431f4d7c29bc643a317e9878028545379b1cf08ec0--gpgme-1.24.2.bottle_manifest.json
==> Downloading https://ghcr.io/v2/homebrew/core/gsettings-desktop-schemas/manifests/48.0
#################################################################################################################################################################################### 100.0%
==> Downloading https://ghcr.io/v2/homebrew/core/at-spi2-core/manifests/2.56.1
#################################################################################################################################################################################### 100.0%
==> Fetching at-spi2-core
==> Downloading https://ghcr.io/v2/homebrew/core/at-spi2-core/blobs/sha256:6dc87b78e3eecf5bd86eca6f60e6b0fd110e65a2404549fb62376f4b41063b8d
#################################################################################################################################################################################### 100.0%
==> Downloading https://ghcr.io/v2/homebrew/core/gtk-mac-integration/manifests/3.0.2
#################################################################################################################################################################################### 100.0%
==> Downloading https://ghcr.io/v2/homebrew/core/tesseract/manifests/5.5.0_1
#################################################################################################################################################################################### 100.0%
==> Fetching tesseract
==> Downloading https://ghcr.io/v2/homebrew/core/tesseract/blobs/sha256:a38cf90d587ff998ce2df8fa9f5092700603f3a11828b964948911b93af532a1
#################################################################################################################################################################################### 100.0%
==> Downloading https://ghcr.io/v2/homebrew/core/ffmpeg/manifests/7.1.1_2
#################################################################################################################################################################################### 100.0%
==> Fetching dependencies for ffmpeg: libidn2, gnutls, mbedtls, libvpx, sdl2, svt-av1 and libarchive
==> Downloading https://ghcr.io/v2/homebrew/core/libidn2/manifests/2.3.8
#################################################################################################################################################################################### 100.0%
==> Fetching libidn2
==> Downloading https://ghcr.io/v2/homebrew/core/libidn2/blobs/sha256:1eb02bfa40ec00b7ea64d8608fcf2115069d99de5a35eb3e2b3ac444a695ea46
#################################################################################################################################################################################### 100.0%
==> Downloading https://ghcr.io/v2/homebrew/core/gnutls/manifests/3.8.9
#################################################################################################################################################################################### 100.0%
==> Fetching gnutls
==> Downloading https://ghcr.io/v2/homebrew/core/gnutls/blobs/sha256:eaf32401a72c80651227e7f5ab70ff762fe7bd990bb566bf4621b37e570ddc66
#################################################################################################################################################################################### 100.0%
==> Downloading https://ghcr.io/v2/homebrew/core/mbedtls/manifests/3.6.3
#################################################################################################################################################################################### 100.0%
==> Fetching mbedtls
==> Downloading https://ghcr.io/v2/homebrew/core/mbedtls/blobs/sha256:d595b50d6404bb6b941f8f3ddc61cee7fe17a669518b5b756b801aae462af4ec
#################################################################################################################################################################################### 100.0%
==> Downloading https://ghcr.io/v2/homebrew/core/libvpx/manifests/1.15.1
#################################################################################################################################################################################### 100.0%
==> Fetching libvpx
==> Downloading https://ghcr.io/v2/homebrew/core/libvpx/blobs/sha256:bb811f6f020d8bc6925bbc2c7fd83b1c0af249771c569ffaff2b7615d3401b45
#################################################################################################################################################################################### 100.0%
==> Downloading https://ghcr.io/v2/homebrew/core/sdl2/manifests/2.32.4-1
#################################################################################################################################################################################### 100.0%
==> Fetching sdl2
==> Downloading https://ghcr.io/v2/homebrew/core/sdl2/blobs/sha256:7aa4224b56ceddc46eedc4cf805ac236fe2d5a5b5b33a93a69b5471dfa43d691
#################################################################################################################################################################################### 100.0%
==> Downloading https://ghcr.io/v2/homebrew/core/svt-av1/manifests/3.0.2
#################################################################################################################################################################################### 100.0%
==> Fetching svt-av1
==> Downloading https://ghcr.io/v2/homebrew/core/svt-av1/blobs/sha256:e93837b76e46e9cfff5d2826fdeb6312842353b899d3e851c81d943e3cb87b57
#################################################################################################################################################################################### 100.0%
==> Downloading https://ghcr.io/v2/homebrew/core/libarchive/manifests/3.7.9
Already downloaded: /Users/valiha/Library/Caches/Homebrew/downloads/f04d01c4b253301055a36f55e16a7ddb02cac054c6d843f01bdf392a444c8e47--libarchive-3.7.9.bottle_manifest.json
==> Fetching libarchive
==> Downloading https://ghcr.io/v2/homebrew/core/libarchive/blobs/sha256:237ddde1af210e9168d6a681dd3f96370f7a19eba17af214b099b4dbf9cda0b1
#################################################################################################################################################################################### 100.0%
==> Fetching ffmpeg
==> Downloading https://ghcr.io/v2/homebrew/core/ffmpeg/blobs/sha256:089a1e82e5fee3c5e01cab1f4fe001b531a5a14e5c2a5e7b1f7c60b09462dfd2
#################################################################################################################################################################################### 100.0%
==> Downloading https://ghcr.io/v2/homebrew/core/ghostscript/manifests/10.05.0_1
#################################################################################################################################################################################### 100.0%
==> Fetching ghostscript
==> Downloading https://ghcr.io/v2/homebrew/core/ghostscript/blobs/sha256:948f72023c7ea36999720a3896e9fe6bd7bca5f729e9542a83898fc466ae5574
#################################################################################################################################################################################### 100.0%
==> Downloading https://ghcr.io/v2/homebrew/core/libraw/manifests/0.21.4
#################################################################################################################################################################################### 100.0%
==> Fetching dependencies for libraw: libomp
==> Downloading https://ghcr.io/v2/homebrew/core/libomp/manifests/20.1.3
#################################################################################################################################################################################### 100.0%
==> Fetching libomp
==> Downloading https://ghcr.io/v2/homebrew/core/libomp/blobs/sha256:70ca0ae9df9f32ef88357ad35efa5b20ee8d91419e385fb0722e52605bceb03b
#################################################################################################################################################################################### 100.0%
==> Fetching libraw
==> Downloading https://ghcr.io/v2/homebrew/core/libraw/blobs/sha256:3ae642e1a337a7183e77b6a3d59fdaf9fa13b56fcd8e565498c494427cc085b3
#################################################################################################################################################################################### 100.0%
==> Downloading https://ghcr.io/v2/homebrew/core/imagemagick/manifests/7.1.1-47-1
#################################################################################################################################################################################### 100.0%
==> Fetching imagemagick
==> Downloading https://ghcr.io/v2/homebrew/core/imagemagick/blobs/sha256:3d7b63545a505aa12f4b9919c03499765b9ae91bb22c171503e00ef1403d447a
#################################################################################################################################################################################### 100.0%
==> Downloading https://ghcr.io/v2/homebrew/core/librsvg/manifests/2.60.0
#################################################################################################################################################################################### 100.0%
==> Fetching dependencies for librsvg: gdk-pixbuf
==> Downloading https://ghcr.io/v2/homebrew/core/gdk-pixbuf/manifests/2.42.12_1
Already downloaded: /Users/valiha/Library/Caches/Homebrew/downloads/2eeb910ea69bc28d9dc0b3b121819ff59ea92fa20bab68c59b6a7a7d5af0708b--gdk-pixbuf-2.42.12_1.bottle_manifest.json
==> Fetching gdk-pixbuf
==> Downloading https://ghcr.io/v2/homebrew/core/gdk-pixbuf/blobs/sha256:64089a3ef04afef0dc8601d22cd534fdc155bef2458bf1a97e6e90f25b7529ad
#################################################################################################################################################################################### 100.0%
==> Fetching librsvg
==> Downloading https://ghcr.io/v2/homebrew/core/librsvg/blobs/sha256:0963c3ac5eab8defa0d871e6f14f376ecb580f87a7369e2d8b6ed1ba5a97b009
#################################################################################################################################################################################### 100.0%
==> Downloading https://ghcr.io/v2/homebrew/core/adwaita-icon-theme/manifests/48.0
#################################################################################################################################################################################### 100.0%
==> Fetching adwaita-icon-theme
==> Downloading https://ghcr.io/v2/homebrew/core/adwaita-icon-theme/blobs/sha256:e14b79a34a4434fee1b94788985410ede2fd9f93b00a7c62a800fde4dfb6b39a
#################################################################################################################################################################################### 100.0%
==> Downloading https://ghcr.io/v2/homebrew/core/libvirt/manifests/11.2.0
#################################################################################################################################################################################### 100.0%
==> Fetching libvirt
==> Downloading https://ghcr.io/v2/homebrew/core/libvirt/blobs/sha256:1e85ba454dfb2f805457d8fbd881c349a39e0fbfd42fc8b0b8bf3ccb48a6b407
#################################################################################################################################################################################### 100.0%
==> Downloading https://ghcr.io/v2/homebrew/core/locust/manifests/2.36.2
#################################################################################################################################################################################### 100.0%
==> Downloading https://ghcr.io/v2/homebrew/core/meson/manifests/1.7.2
#################################################################################################################################################################################### 100.0%
==> Fetching meson
==> Downloading https://ghcr.io/v2/homebrew/core/meson/blobs/sha256:7743e7a1a73ed85500ee7f73307f718bae8ea9d74bde0494726aee656c69fd54
#################################################################################################################################################################################### 100.0%
==> Downloading https://ghcr.io/v2/homebrew/core/netpbm/manifests/11.02.15
#################################################################################################################################################################################### 100.0%
==> Fetching netpbm
==> Downloading https://ghcr.io/v2/homebrew/core/netpbm/blobs/sha256:654efca03d75a2a9d35af20ab312b2929baefefefb23c12a63372733913ceeba
#################################################################################################################################################################################### 100.0%
==> Downloading https://ghcr.io/v2/homebrew/core/numpy/manifests/2.2.5
#################################################################################################################################################################################### 100.0%
==> Fetching dependencies for numpy: mpfr
==> Downloading https://ghcr.io/v2/homebrew/core/mpfr/manifests/4.2.2
#################################################################################################################################################################################### 100.0%
==> Fetching mpfr
==> Downloading https://ghcr.io/v2/homebrew/core/mpfr/blobs/sha256:ed822b7e77645d7c17abb3ee9cc2b2a82a4d0f003acc7615b5df6226031479b2
#################################################################################################################################################################################### 100.0%
==> Fetching numpy
==> Downloading https://ghcr.io/v2/homebrew/core/numpy/blobs/sha256:ada13da2a330ff6e0f36050853d87dc84dca63bb0ac17e4ca0e5d233a9a6f343
#################################################################################################################################################################################### 100.0%
==> Downloading https://ghcr.io/v2/homebrew/core/py3cairo/manifests/1.28.0
#################################################################################################################################################################################### 100.0%
==> Fetching py3cairo
==> Downloading https://ghcr.io/v2/homebrew/core/py3cairo/blobs/sha256:a3215f667bbecd5f84bd93fe29455894e9b051c088f69199224477652882f412
#################################################################################################################################################################################### 100.0%
==> Downloading https://ghcr.io/v2/homebrew/core/pygobject3/manifests/3.52.3
#################################################################################################################################################################################### 100.0%
==> Fetching pygobject3
==> Downloading https://ghcr.io/v2/homebrew/core/pygobject3/blobs/sha256:b8d91047912ee452e7b000c29413dc0646134deee82d94181c8063ab5f33fd70
#################################################################################################################################################################################### 100.0%
==> Downloading https://ghcr.io/v2/homebrew/core/uhd/manifests/4.8.0.0_1
#################################################################################################################################################################################### 100.0%
==> Downloading https://ghcr.io/v2/homebrew/core/gnuradio/manifests/3.10.12.0_1
#################################################################################################################################################################################### 100.0%
==> Fetching dependencies for gnuradio: pmix, gsettings-desktop-schemas, rpds-py, spdlog and uhd
==> Downloading https://ghcr.io/v2/homebrew/core/pmix/manifests/5.0.7
#################################################################################################################################################################################### 100.0%
==> Fetching pmix
==> Downloading https://ghcr.io/v2/homebrew/core/pmix/blobs/sha256:4e59d8ac974bb4044d20819bc706546f0be8d4f93d2606fba9955cf7ef5b3e79
#################################################################################################################################################################################### 100.0%
==> Downloading https://ghcr.io/v2/homebrew/core/gsettings-desktop-schemas/manifests/48.0
Already downloaded: /Users/valiha/Library/Caches/Homebrew/downloads/b50977acc6e572c3fef03f9e0d5a91fb31313e24dce8cea5c0cedcc626a07b3b--gsettings-desktop-schemas-48.0.bottle_manifest.json
==> Fetching gsettings-desktop-schemas
==> Downloading https://ghcr.io/v2/homebrew/core/gsettings-desktop-schemas/blobs/sha256:28388575b4cdde9dbca9351e2589c4445e531fb7e4fa43905d96d3d89dd78d29
#################################################################################################################################################################################### 100.0%
==> Downloading https://ghcr.io/v2/homebrew/core/rpds-py/manifests/0.24.0
#################################################################################################################################################################################### 100.0%
==> Fetching rpds-py
==> Downloading https://ghcr.io/v2/homebrew/core/rpds-py/blobs/sha256:fd53408b3574c7b3198ab7bf52d34e31c14c99715293ea1bd41bb3aa6127ebaf
#################################################################################################################################################################################### 100.0%
==> Downloading https://ghcr.io/v2/homebrew/core/spdlog/manifests/1.15.2
#################################################################################################################################################################################### 100.0%
==> Fetching spdlog
==> Downloading https://ghcr.io/v2/homebrew/core/spdlog/blobs/sha256:fce7e7460c9221b3cac3d0217cc0308805c7c30e4a01fcd7a8e76639029e6b67
#################################################################################################################################################################################### 100.0%
==> Downloading https://ghcr.io/v2/homebrew/core/uhd/manifests/4.8.0.0_1
Already downloaded: /Users/valiha/Library/Caches/Homebrew/downloads/1fa414e4d81cc165453c8a6f063e090f67f2600b0f975aa60981a4b8ee85779b--uhd-4.8.0.0_1.bottle_manifest.json
==> Fetching uhd
==> Downloading https://ghcr.io/v2/homebrew/core/uhd/blobs/sha256:ebaad7dcd0a6646f5bba5fb5d2ec4741caba9c9512a40ccc45876b91adda40f9
#################################################################################################################################################################################### 100.0%
==> Fetching gnuradio
==> Downloading https://ghcr.io/v2/homebrew/core/gnuradio/blobs/sha256:764d4cd2ae0dfd4d3bdb4fb3b7c7bcb947f7758449ecb38f1daca1383a0ee748
#################################################################################################################################################################################### 100.0%
==> Downloading https://ghcr.io/v2/homebrew/core/openfpgaloader/manifests/0.13.1
Already downloaded: /Users/valiha/Library/Caches/Homebrew/downloads/77fc48bda99c8da03cb536588d383b7fb87ecad96d06f03bfb37225baa398751--openfpgaloader-0.13.1.bottle_manifest.json
==> Downloading https://ghcr.io/v2/homebrew/core/poppler/manifests/25.04.0
#################################################################################################################################################################################### 100.0%
==> Fetching dependencies for poppler: libassuan, gpgme and nss
==> Downloading https://ghcr.io/v2/homebrew/core/libassuan/manifests/3.0.2
Already downloaded: /Users/valiha/Library/Caches/Homebrew/downloads/0fcd4af28064aef7277b774e3698e36630214907b803972d6722ec02a47a59cd--libassuan-3.0.2.bottle_manifest.json
==> Fetching libassuan
==> Downloading https://ghcr.io/v2/homebrew/core/libassuan/blobs/sha256:1430611fe9f337d6a7568a12321f125c567ca8d4d2bdcd7ff0717bdcd82a32dc
#################################################################################################################################################################################### 100.0%
==> Downloading https://ghcr.io/v2/homebrew/core/gpgme/manifests/1.24.2
Already downloaded: /Users/valiha/Library/Caches/Homebrew/downloads/b27e679213b6f16659cc6b431f4d7c29bc643a317e9878028545379b1cf08ec0--gpgme-1.24.2.bottle_manifest.json
==> Fetching gpgme
==> Downloading https://ghcr.io/v2/homebrew/core/gpgme/blobs/sha256:f050cd4be93a9a506d374f44be63b13f0063bea568c7508c947be36cd4fcf510
#################################################################################################################################################################################### 100.0%
==> Downloading https://ghcr.io/v2/homebrew/core/nss/manifests/3.110
#################################################################################################################################################################################### 100.0%
==> Fetching nss
==> Downloading https://ghcr.io/v2/homebrew/core/nss/blobs/sha256:8ce72d9fb7a72fca71ea3a2e9c5971c4815dc9e14a4d125bda30a30eea7086a7
#################################################################################################################################################################################### 100.0%
==> Fetching poppler
==> Downloading https://ghcr.io/v2/homebrew/core/poppler/blobs/sha256:a29d98c0879d478396207cf4ada42d58181a87e237ee5e137effeb70fcf4713c
#################################################################################################################################################################################### 100.0%
==> Downloading https://ghcr.io/v2/homebrew/core/pyenv/manifests/2.5.5
#################################################################################################################################################################################### 100.0%
==> Downloading https://ghcr.io/v2/homebrew/core/pyqt/manifests/6.9.0
#################################################################################################################################################################################### 100.0%
==> Fetching pyqt
==> Downloading https://ghcr.io/v2/homebrew/core/pyqt/blobs/sha256:9d2e7040345f46c69227e5dd30def0a1c0476514d243e5b5dead7d41d56afa4c
#################################################################################################################################################################################### 100.0%
==> Downloading https://ghcr.io/v2/homebrew/core/python-argcomplete/manifests/3.6.2
#################################################################################################################################################################################### 100.0%
==> Downloading https://ghcr.io/v2/homebrew/core/python/3.10/manifests/3.10.17
#################################################################################################################################################################################### 100.0%
==> Fetching dependencies for python@3.10: gdbm
==> Downloading https://ghcr.io/v2/homebrew/core/gdbm/manifests/1.25
#################################################################################################################################################################################### 100.0%
==> Fetching gdbm
==> Downloading https://ghcr.io/v2/homebrew/core/gdbm/blobs/sha256:ce13d6f53ca09fb01e34f336ed2ba2660d8fd107bc1d374ea12cbd94e3bd2c10
#################################################################################################################################################################################### 100.0%
==> Fetching python@3.10
==> Downloading https://ghcr.io/v2/homebrew/core/python/3.10/blobs/sha256:7fb330605dcc89c705fa2e8be8658d0781c1637d689c90794181a9a1b61dabaf
#################################################################################################################################################################################### 100.0%
==> Downloading https://ghcr.io/v2/homebrew/core/python/3.11/manifests/3.11.12
#################################################################################################################################################################################### 100.0%
==> Downloading https://ghcr.io/v2/homebrew/core/python/3.12/manifests/3.12.10-1
#################################################################################################################################################################################### 100.0%
==> Downloading https://ghcr.io/v2/homebrew/core/qemu/manifests/10.0.0
#################################################################################################################################################################################### 100.0%
==> Fetching dependencies for qemu: capstone
==> Downloading https://ghcr.io/v2/homebrew/core/capstone/manifests/5.0.5
Already downloaded: /Users/valiha/Library/Caches/Homebrew/downloads/c0c0dfcac152442240eb9c849b2694a9d2d35ce93b92e701037188322abc8b6c--capstone-5.0.5.bottle_manifest.json
==> Fetching capstone
==> Downloading https://ghcr.io/v2/homebrew/core/capstone/blobs/sha256:1c3da7d71701212fee2fc19fff9bf62096d490c17e60b4eec455628270b0ded5
#################################################################################################################################################################################### 100.0%
==> Fetching qemu
==> Downloading https://ghcr.io/v2/homebrew/core/qemu/blobs/sha256:7d913e1a285f40bf5b7d66d9e202684b627c0da56531c0ad8164794b12ef3c6a
#################################################################################################################################################################################### 100.0%
==> Downloading https://ghcr.io/v2/homebrew/core/suite-sparse/manifests/7.10.2
#################################################################################################################################################################################### 100.0%
==> Fetching suite-sparse
==> Downloading https://ghcr.io/v2/homebrew/core/suite-sparse/blobs/sha256:23972845c3198d20131fe22e03f4bedafc1771cefbc4bbc5a7511b2ced2f0c1d
#################################################################################################################################################################################### 100.0%
==> Downloading https://ghcr.io/v2/homebrew/core/sundials/manifests/7.3.0
#################################################################################################################################################################################### 100.0%
==> Fetching sundials
==> Downloading https://ghcr.io/v2/homebrew/core/sundials/blobs/sha256:4ecec4e8bf4e1b6e572703cf17f0bfcb9285455dee39c16e35faa27f99f0fdaf
#################################################################################################################################################################################### 100.0%
==> Downloading https://ghcr.io/v2/homebrew/core/texlive/manifests/20250308_1
#################################################################################################################################################################################### 100.0%
==> Fetching dependencies for texlive: luajit, openjdk and perl
==> Downloading https://ghcr.io/v2/homebrew/core/luajit/manifests/2.1.1744318430
#################################################################################################################################################################################### 100.0%
==> Fetching luajit
==> Downloading https://ghcr.io/v2/homebrew/core/luajit/blobs/sha256:72a8213363c598f8ed1bcd607ed934d591fe97f22f06bffdd8f3b97fd34c5e44
#################################################################################################################################################################################### 100.0%
==> Downloading https://ghcr.io/v2/homebrew/core/openjdk/manifests/23.0.2
Already downloaded: /Users/valiha/Library/Caches/Homebrew/downloads/8dea1e6c16fdb5358c4865d24639ab139310acfcd2a8472a89f458bbb046eac5--openjdk-23.0.2.bottle_manifest.json
==> Fetching openjdk
==> Downloading https://ghcr.io/v2/homebrew/core/openjdk/blobs/sha256:1285eadf2b5998cda49e4470ee3875e855b0be199765401ad77dc38aea573f49
#################################################################################################################################################################################### 100.0%
==> Downloading https://ghcr.io/v2/homebrew/core/perl/manifests/5.40.2
#################################################################################################################################################################################### 100.0%
==> Fetching perl
==> Downloading https://ghcr.io/v2/homebrew/core/perl/blobs/sha256:c984a79cf9dba490a830081f3587349723c8c156b79dc7b6c159360624181299
#################################################################################################################################################################################### 100.0%
==> Fetching texlive
==> Downloading https://ghcr.io/v2/homebrew/core/texlive/blobs/sha256:dbb0b1a2a0b1d06263f2fe4e1b386cc2f682c4ab3a5d399b65cbfb3ce33ce4eb
#################################################################################################################################################################################### 100.0%
==> Downloading https://ghcr.io/v2/homebrew/core/wireshark/manifests/4.4.6
#################################################################################################################################################################################### 100.0%
==> Fetching dependencies for wireshark: c-ares, libgpg-error and libnghttp3
==> Downloading https://ghcr.io/v2/homebrew/core/c-ares/manifests/1.34.5
#################################################################################################################################################################################### 100.0%
==> Fetching c-ares
==> Downloading https://ghcr.io/v2/homebrew/core/c-ares/blobs/sha256:d56159131f89594ce18c3ec3c265c35781e7e516386dbc09cc19a670605b2eba
#################################################################################################################################################################################### 100.0%
==> Downloading https://ghcr.io/v2/homebrew/core/libgpg-error/manifests/1.55
#################################################################################################################################################################################### 100.0%
==> Fetching libgpg-error
==> Downloading https://ghcr.io/v2/homebrew/core/libgpg-error/blobs/sha256:a2d0e274ace59980a81d2b06c445ddef5498c69cbefc85bdf04d3d79d0dfd71d
#################################################################################################################################################################################### 100.0%
==> Downloading https://ghcr.io/v2/homebrew/core/libnghttp3/manifests/1.9.0
#################################################################################################################################################################################### 100.0%
==> Fetching libnghttp3
==> Downloading https://ghcr.io/v2/homebrew/core/libnghttp3/blobs/sha256:07df76d04a3b7879cc6669a4da943f26190d90f997a032d299bc5e63dab18f65
#################################################################################################################################################################################### 100.0%
==> Fetching wireshark
==> Downloading https://ghcr.io/v2/homebrew/core/wireshark/blobs/sha256:ce24d43d2ed69bfd9d45f45f2a50457dea8edcc2e9fdafe178c777f6ecd5bff3
#################################################################################################################################################################################### 100.0%
==> Downloading https://ghcr.io/v2/homebrew/core/yt-dlp/manifests/2025.3.31
#################################################################################################################################################################################### 100.0%
==> Downloading https://ghcr.io/v2/homebrew/core/azure-cli/manifests/2.71.0
#################################################################################################################################################################################### 100.0%
==> Upgrading harfbuzz
  10.4.0 -> 11.1.0 
==> Installing dependencies for harfbuzz: libx11 and cairo
==> Installing harfbuzz dependency: libx11
==> Downloading https://ghcr.io/v2/homebrew/core/libx11/manifests/1.8.12
Already downloaded: /Users/valiha/Library/Caches/Homebrew/downloads/8510ddcf75e7c4313fe4f8b0999d667b22f2ae0b850bc80ba53becb609335934--libx11-1.8.12.bottle_manifest.json
==> Pouring libx11--1.8.12.arm64_sequoia.bottle.tar.gz
🍺  /opt/homebrew/Cellar/libx11/1.8.12: 1,043 files, 7MB
==> Installing harfbuzz dependency: cairo
==> Downloading https://ghcr.io/v2/homebrew/core/cairo/manifests/1.18.4
Already downloaded: /Users/valiha/Library/Caches/Homebrew/downloads/795ef2e2e2a57e6baba0fc9ceedb58980e8ec718aba0170b9441a0b25442cfbf--cairo-1.18.4.bottle_manifest.json
==> Pouring cairo--1.18.4.arm64_sequoia.bottle.tar.gz
🍺  /opt/homebrew/Cellar/cairo/1.18.4: 53 files, 2.2MB
==> Installing harfbuzz
==> Pouring harfbuzz--11.1.0.arm64_sequoia.bottle.tar.gz
🍺  /opt/homebrew/Cellar/harfbuzz/11.1.0: 77 files, 10.0MB
==> Running `brew cleanup harfbuzz`...
Removing: /opt/homebrew/Cellar/harfbuzz/10.4.0... (77 files, 9.9MB)
Removing: /Users/valiha/Library/Caches/Homebrew/harfbuzz_bottle_manifest--10.4.0... (23.8KB)
Removing: /Users/valiha/Library/Caches/Homebrew/harfbuzz--10.4.0... (2.5MB)
==> Upgrading llvm
  19.1.7_1 -> 20.1.3 
==> Installing dependencies for llvm: z3
==> Installing llvm dependency: z3
==> Downloading https://ghcr.io/v2/homebrew/core/z3/manifests/4.14.1
Already downloaded: /Users/valiha/Library/Caches/Homebrew/downloads/0eeec45732524251dbe18a67dc5f0a626fdab7ae2432a0a3dab5e4d36a4212b5--z3-4.14.1.bottle_manifest.json
==> Pouring z3--4.14.1.arm64_sequoia.bottle.tar.gz
🍺  /opt/homebrew/Cellar/z3/4.14.1: 120 files, 32.7MB
==> Installing llvm
==> Pouring llvm--20.1.3.arm64_sequoia.bottle.tar.gz
==> Downloading https://formulae.brew.sh/api/formula.jws.json
==> Caveats
CLANG_CONFIG_FILE_SYSTEM_DIR: /opt/homebrew/etc/clang
CLANG_CONFIG_FILE_USER_DIR:   ~/.config/clang

LLD is now provided in a separate formula:
  brew install lld

Using `clang`, `clang++`, etc., requires a CLT installation at `/Library/Developer/CommandLineTools`.
If you don't want to install the CLT, you can write appropriate configuration files pointing to your
SDK at ~/.config/clang.

To use the bundled libunwind please use the following LDFLAGS:
  LDFLAGS="-L/opt/homebrew/opt/llvm/lib/unwind -lunwind"

To use the bundled libc++ please use the following LDFLAGS:
  LDFLAGS="-L/opt/homebrew/opt/llvm/lib/c++ -L/opt/homebrew/opt/llvm/lib/unwind -lunwind"

NOTE: You probably want to use the libunwind and libc++ provided by macOS unless you know what you're doing.

llvm is keg-only, which means it was not symlinked into /opt/homebrew,
because macOS already provides this software and installing another version in
parallel can cause all kinds of trouble.

If you need to have llvm first in your PATH, run:
  echo 'export PATH="/opt/homebrew/opt/llvm/bin:$PATH"' >> ~/.zshrc

For compilers to find llvm you may need to set:
  export LDFLAGS="-L/opt/homebrew/opt/llvm/lib"
  export CPPFLAGS="-I/opt/homebrew/opt/llvm/include"
==> Summary
🍺  /opt/homebrew/Cellar/llvm/20.1.3: 9,417 files, 1.6GB
==> Running `brew cleanup llvm`...
Removing: /opt/homebrew/Cellar/llvm/19.1.7_1... (8,107 files, 1.9GB)
Removing: /Users/valiha/Library/Caches/Homebrew/llvm_bottle_manifest--19.1.7_1... (33.9KB)
Removing: /Users/valiha/Library/Caches/Homebrew/llvm--19.1.7_1... (490.2MB)
==> Upgrading ccache
  4.10.2_3 -> 4.11.2 
==> Installing dependencies for ccache: blake3, fmt and xxhash
==> Installing ccache dependency: blake3
==> Downloading https://ghcr.io/v2/homebrew/core/blake3/manifests/1.8.2
Already downloaded: /Users/valiha/Library/Caches/Homebrew/downloads/fd8aa2201dffd4a0db6644c9eff70b8c0d1a0a643ed362fc54f77d3a80fd3478--blake3-1.8.2.bottle_manifest.json
==> Pouring blake3--1.8.2.arm64_sequoia.bottle.tar.gz
🍺  /opt/homebrew/Cellar/blake3/1.8.2: 13 files, 94.8KB
==> Installing ccache dependency: fmt
==> Downloading https://ghcr.io/v2/homebrew/core/fmt/manifests/11.1.4
Already downloaded: /Users/valiha/Library/Caches/Homebrew/downloads/c9873831dda0fef5a91b23679ee3757d99496c92066bb38180b4e1bcaf9be074--fmt-11.1.4.bottle_manifest.json
==> Pouring fmt--11.1.4.arm64_sequoia.bottle.tar.gz
🍺  /opt/homebrew/Cellar/fmt/11.1.4: 29 files, 1MB
==> Installing ccache dependency: xxhash
==> Downloading https://ghcr.io/v2/homebrew/core/xxhash/manifests/0.8.3
Already downloaded: /Users/valiha/Library/Caches/Homebrew/downloads/50d7a45c8aca7a38ebe38c4b8fb63fa7404dc4c360092f1e301c275fcc585cf0--xxhash-0.8.3.bottle_manifest.json
==> Pouring xxhash--0.8.3.arm64_sequoia.bottle.tar.gz
🍺  /opt/homebrew/Cellar/xxhash/0.8.3: 28 files, 544.0KB
==> Installing ccache
==> Pouring ccache--4.11.2.arm64_sequoia.bottle.tar.gz
==> Caveats
To install symlinks for compilers that will automatically use
ccache, prepend this directory to your PATH:
  /opt/homebrew/opt/ccache/libexec

If this is an upgrade and you have previously added the symlinks to
your PATH, you may need to modify it to the path specified above so
it points to the current version.

NOTE: ccache can prevent some software from compiling.
ALSO NOTE: The brew command, by design, will never use ccache.
==> Summary
🍺  /opt/homebrew/Cellar/ccache/4.11.2: 82 files, 1.4MB
==> Running `brew cleanup ccache`...
Removing: /opt/homebrew/Cellar/ccache/4.10.2_3... (82 files, 1.4MB)
Removing: /Users/valiha/Library/Caches/Homebrew/ccache_bottle_manifest--4.10.2_3... (13.7KB)
Removing: /Users/valiha/Library/Caches/Homebrew/ccache--4.10.2_3... (471.4KB)
==> Upgrading jpeg-xl
  0.11.1 -> 0.11.1_1 
==> Installing dependencies for jpeg-xl: openexr
==> Installing jpeg-xl dependency: openexr
==> Downloading https://ghcr.io/v2/homebrew/core/openexr/manifests/3.3.3
Already downloaded: /Users/valiha/Library/Caches/Homebrew/downloads/661875a911e1a6eec294e6d3b7ce82ec158406213d516e898ccafa62fa56481e--openexr-3.3.3.bottle_manifest.json
==> Pouring openexr--3.3.3.arm64_sequoia.bottle.tar.gz
🍺  /opt/homebrew/Cellar/openexr/3.3.3: 210 files, 4.8MB
==> Installing jpeg-xl
==> Pouring jpeg-xl--0.11.1_1.arm64_sequoia.bottle.tar.gz
🍺  /opt/homebrew/Cellar/jpeg-xl/0.11.1_1: 64 files, 35MB
==> Running `brew cleanup jpeg-xl`...
Removing: /opt/homebrew/Cellar/jpeg-xl/0.11.1... (64 files, 35MB)
==> Upgrading aom
  3.12.0 -> 3.12.1 
==> Pouring aom--3.12.1.arm64_sequoia.bottle.tar.gz
🍺  /opt/homebrew/Cellar/aom/3.12.1: 24 files, 9.8MB
==> Running `brew cleanup aom`...
Removing: /opt/homebrew/Cellar/aom/3.12.0... (24 files, 9.8MB)
Removing: /Users/valiha/Library/Caches/Homebrew/aom_bottle_manifest--3.12.0... (20.2KB)
Removing: /Users/valiha/Library/Caches/Homebrew/aom--3.12.0... (3.9MB)
==> Upgrading pango
  1.56.1 -> 1.56.3 
==> Pouring pango--1.56.3.arm64_sequoia.bottle.tar.gz
🍺  /opt/homebrew/Cellar/pango/1.56.3: 69 files, 3.4MB
==> Running `brew cleanup pango`...
Removing: /opt/homebrew/Cellar/pango/1.56.1... (69 files, 3.4MB)
Removing: /Users/valiha/Library/Caches/Homebrew/pango_bottle_manifest--1.56.1... (30.0KB)
Removing: /Users/valiha/Library/Caches/Homebrew/pango--1.56.1... (828KB)
==> Upgrading qt
  6.8.2 -> 6.9.0 
==> Installing dependencies for qt: dbus, double-conversion and jasper
==> Installing qt dependency: dbus
==> Downloading https://ghcr.io/v2/homebrew/core/dbus/manifests/1.16.2
Already downloaded: /Users/valiha/Library/Caches/Homebrew/downloads/4d7addc05476f068c217c8e9d9c3a43fd366359d34bd4ad056d0de7568cd8847--dbus-1.16.2.bottle_manifest.json
==> Pouring dbus--1.16.2.arm64_sequoia.bottle.tar.gz
==> /opt/homebrew/Cellar/dbus/1.16.2/bin/dbus-uuidgen --ensure=/opt/homebrew/var/lib/dbus/machine-id
🍺  /opt/homebrew/Cellar/dbus/1.16.2: 78 files, 2MB
==> Installing qt dependency: double-conversion
==> Downloading https://ghcr.io/v2/homebrew/core/double-conversion/manifests/3.3.1
Already downloaded: /Users/valiha/Library/Caches/Homebrew/downloads/ea562cf5822e1db7583f6877e2ab750797cff74d91969299f5a2635e9a0e2fb2--double-conversion-3.3.1.bottle_manifest.json
==> Pouring double-conversion--3.3.1.arm64_sequoia.bottle.tar.gz
🍺  /opt/homebrew/Cellar/double-conversion/3.3.1: 28 files, 267.9KB
==> Installing qt dependency: jasper
==> Downloading https://ghcr.io/v2/homebrew/core/jasper/manifests/4.2.5
Already downloaded: /Users/valiha/Library/Caches/Homebrew/downloads/0b7879dee43d75b41e26cd2680fb480d314374076cdd50feb7f4ed998ab38964--jasper-4.2.5.bottle_manifest.json
==> Pouring jasper--4.2.5.arm64_sequoia.bottle.tar.gz
🍺  /opt/homebrew/Cellar/jasper/4.2.5: 45 files, 1.6MB
==> Installing qt
==> Pouring qt--6.9.0.arm64_sonoma.bottle.tar.gz
🍺  /opt/homebrew/Cellar/qt/6.9.0: 18,380 files, 774.4MB
==> Running `brew cleanup qt`...
Removing: /opt/homebrew/Cellar/qt/6.8.2... (16,995 files, 727.9MB)
Removing: /Users/valiha/Library/Caches/Homebrew/qt_bottle_manifest--6.8.2... (101.4KB)
Removing: /Users/valiha/Library/Caches/Homebrew/qt--6.8.2... (198.4MB)
==> Upgrading gnuplot
  6.0.2 -> 6.0.2_1 
==> Installing dependencies for gnuplot: libavif and libcerf
==> Installing gnuplot dependency: libavif
==> Downloading https://ghcr.io/v2/homebrew/core/libavif/manifests/1.2.1
Already downloaded: /Users/valiha/Library/Caches/Homebrew/downloads/a3880a25438e74c798bd1fc9305af44be3f3680e04c511626de04a030cf1838d--libavif-1.2.1.bottle_manifest.json
==> Pouring libavif--1.2.1.arm64_sequoia.bottle.tar.gz
🍺  /opt/homebrew/Cellar/libavif/1.2.1: 22 files, 992.8KB
==> Installing gnuplot dependency: libcerf
==> Downloading https://ghcr.io/v2/homebrew/core/libcerf/manifests/3.0
Already downloaded: /Users/valiha/Library/Caches/Homebrew/downloads/f5a8f4cfea31821e739573783a2177e9facb6a8d18d867a855377bd18b9a894d--libcerf-3.0.bottle_manifest.json
==> Pouring libcerf--3.0.arm64_sequoia.bottle.tar.gz
🍺  /opt/homebrew/Cellar/libcerf/3.0: 42 files, 302.5KB
==> Installing gnuplot
==> Pouring gnuplot--6.0.2_1.arm64_sonoma.bottle.tar.gz
🍺  /opt/homebrew/Cellar/gnuplot/6.0.2_1: 48 files, 3MB
==> Running `brew cleanup gnuplot`...
Removing: /opt/homebrew/Cellar/gnuplot/6.0.2... (48 files, 3MB)
Removing: /Users/valiha/Library/Caches/Homebrew/gnuplot_bottle_manifest--6.0.2... (60.3KB)
Removing: /Users/valiha/Library/Caches/Homebrew/gnuplot--6.0.2... (1.1MB)
==> Upgrading gobject-introspection
  1.82.0 -> 1.84.0 
==> Pouring gobject-introspection--1.84.0.arm64_sequoia.bottle.tar.gz
🍺  /opt/homebrew/Cellar/gobject-introspection/1.84.0: 781 files, 7.5MB
==> Running `brew cleanup gobject-introspection`...
Removing: /opt/homebrew/Cellar/gobject-introspection/1.82.0... (833 files, 7.4MB)
==> Upgrading at-spi2-core
  2.54.1 -> 2.56.1 
==> Pouring at-spi2-core--2.56.1.arm64_sequoia.bottle.tar.gz
🍺  /opt/homebrew/Cellar/at-spi2-core/2.56.1: 201 files, 4.3MB
==> Running `brew cleanup at-spi2-core`...
Removing: /opt/homebrew/Cellar/at-spi2-core/2.54.1... (200 files, 4.3MB)
Removing: /Users/valiha/Library/Caches/Homebrew/at-spi2-core_bottle_manifest--2.54.1... (25.7KB)
Removing: /Users/valiha/Library/Caches/Homebrew/at-spi2-core--2.54.1... (787.4KB)
==> Upgrading tesseract
  5.5.0 -> 5.5.0_1 
==> Pouring tesseract--5.5.0_1.arm64_sequoia.bottle.tar.gz
==> Caveats
This formula contains only the "eng", "osd", and "snum" language data files.
If you need any other supported languages, run `brew install tesseract-lang`.
==> Summary
🍺  /opt/homebrew/Cellar/tesseract/5.5.0_1: 75 files, 33.1MB
==> Running `brew cleanup tesseract`...
Removing: /opt/homebrew/Cellar/tesseract/5.5.0... (75 files, 33MB)
==> Upgrading ffmpeg
  7.1.1 -> 7.1.1_2 
==> Installing dependencies for ffmpeg: libidn2, gnutls, mbedtls, libvpx, sdl2, svt-av1 and libarchive
==> Installing ffmpeg dependency: libidn2
==> Downloading https://ghcr.io/v2/homebrew/core/libidn2/manifests/2.3.8
Already downloaded: /Users/valiha/Library/Caches/Homebrew/downloads/f30f50fbde4bff9a71de54d684e482d7da3432656d680b97441163c6e5665468--libidn2-2.3.8.bottle_manifest.json
==> Pouring libidn2--2.3.8.arm64_sequoia.bottle.tar.gz
🍺  /opt/homebrew/Cellar/libidn2/2.3.8: 80 files, 929.5KB
==> Installing ffmpeg dependency: gnutls
==> Downloading https://ghcr.io/v2/homebrew/core/gnutls/manifests/3.8.9
Already downloaded: /Users/valiha/Library/Caches/Homebrew/downloads/aa9854d92d160da79cf6db83ae63d51f5c7d13682658fa43a335e4108af40362--gnutls-3.8.9.bottle_manifest.json
==> Pouring gnutls--3.8.9.arm64_sequoia.bottle.tar.gz
🍺  /opt/homebrew/Cellar/gnutls/3.8.9: 1,296 files, 11.0MB
==> Installing ffmpeg dependency: mbedtls
==> Downloading https://ghcr.io/v2/homebrew/core/mbedtls/manifests/3.6.3
Already downloaded: /Users/valiha/Library/Caches/Homebrew/downloads/3efc35a2d4e62fd971eb6c5f66d35675f4fe4cbb3e746122b37be011a573f3d8--mbedtls-3.6.3.bottle_manifest.json
==> Pouring mbedtls--3.6.3.arm64_sequoia.bottle.tar.gz
🍺  /opt/homebrew/Cellar/mbedtls/3.6.3: 198 files, 13.3MB
==> Installing ffmpeg dependency: libvpx
==> Downloading https://ghcr.io/v2/homebrew/core/libvpx/manifests/1.15.1
Already downloaded: /Users/valiha/Library/Caches/Homebrew/downloads/867634cbe0e9b126fc489d210fd7541eaa030b9c8725937cecb11853850f08b2--libvpx-1.15.1.bottle_manifest.json
==> Pouring libvpx--1.15.1.arm64_sequoia.bottle.tar.gz
🍺  /opt/homebrew/Cellar/libvpx/1.15.1: 22 files, 4.1MB
==> Installing ffmpeg dependency: sdl2
==> Downloading https://ghcr.io/v2/homebrew/core/sdl2/manifests/2.32.4-1
Already downloaded: /Users/valiha/Library/Caches/Homebrew/downloads/19a61f83e224c628352e0a006f92fe25aff996b6f871d76e131b71ae4001e67b--sdl2-2.32.4-1.bottle_manifest.json
==> Pouring sdl2--2.32.4.arm64_sequoia.bottle.1.tar.gz
🍺  /opt/homebrew/Cellar/sdl2/2.32.4: 94 files, 6.4MB
==> Installing ffmpeg dependency: svt-av1
==> Downloading https://ghcr.io/v2/homebrew/core/svt-av1/manifests/3.0.2
Already downloaded: /Users/valiha/Library/Caches/Homebrew/downloads/08b707c1ceca9182539fadceb56d5017860f66e31092634bd65d4ee476c6f02d--svt-av1-3.0.2.bottle_manifest.json
==> Pouring svt-av1--3.0.2.arm64_sequoia.bottle.tar.gz
🍺  /opt/homebrew/Cellar/svt-av1/3.0.2: 18 files, 3.2MB
==> Installing ffmpeg dependency: libarchive
==> Downloading https://ghcr.io/v2/homebrew/core/libarchive/manifests/3.7.9
Already downloaded: /Users/valiha/Library/Caches/Homebrew/downloads/f04d01c4b253301055a36f55e16a7ddb02cac054c6d843f01bdf392a444c8e47--libarchive-3.7.9.bottle_manifest.json
==> Pouring libarchive--3.7.9.arm64_sequoia.bottle.tar.gz
🍺  /opt/homebrew/Cellar/libarchive/3.7.9: 65 files, 3.8MB
==> Installing ffmpeg
==> Pouring ffmpeg--7.1.1_2.arm64_sequoia.bottle.tar.gz
🍺  /opt/homebrew/Cellar/ffmpeg/7.1.1_2: 287 files, 52.1MB
==> Running `brew cleanup ffmpeg`...
Removing: /opt/homebrew/Cellar/ffmpeg/7.1.1... (287 files, 52.1MB)
Removing: /Users/valiha/Library/Caches/Homebrew/ffmpeg_bottle_manifest--7.1.1... (81.1KB)
Removing: /Users/valiha/Library/Caches/Homebrew/ffmpeg--7.1.1... (20.2MB)
==> Upgrading ghostscript
  10.04.0 -> 10.05.0_1 
==> Pouring ghostscript--10.05.0_1.arm64_sequoia.bottle.tar.gz
🍺  /opt/homebrew/Cellar/ghostscript/10.05.0_1: 638 files, 122MB
==> Running `brew cleanup ghostscript`...
Removing: /opt/homebrew/Cellar/ghostscript/10.04.0... (640 files, 121.9MB)
==> Upgrading libraw
  0.21.3 -> 0.21.4 
==> Installing dependencies for libraw: libomp
==> Installing libraw dependency: libomp
==> Downloading https://ghcr.io/v2/homebrew/core/libomp/manifests/20.1.3
Already downloaded: /Users/valiha/Library/Caches/Homebrew/downloads/6fb106d95811ad1827b4ad653f3b94cb6dd44ceb8a4a4fb00355021f4d682a56--libomp-20.1.3.bottle_manifest.json
==> Pouring libomp--20.1.3.arm64_sequoia.bottle.tar.gz
🍺  /opt/homebrew/Cellar/libomp/20.1.3: 9 files, 1.7MB
==> Installing libraw
==> Pouring libraw--0.21.4.arm64_sequoia.bottle.tar.gz
🍺  /opt/homebrew/Cellar/libraw/0.21.4: 74 files, 6.0MB
==> Running `brew cleanup libraw`...
Removing: /opt/homebrew/Cellar/libraw/0.21.3... (74 files, 5.9MB)
==> Upgrading imagemagick
  7.1.1-44 -> 7.1.1-47 
==> Pouring imagemagick--7.1.1-47.arm64_sequoia.bottle.1.tar.gz
==> Caveats
Ghostscript is not installed by default as a dependency.
If you need PS or PDF support, ImageMagick will still use the ghostscript formula if installed directly.
==> Summary
🍺  /opt/homebrew/Cellar/imagemagick/7.1.1-47: 809 files, 32.4MB
==> Running `brew cleanup imagemagick`...
Removing: /opt/homebrew/Cellar/imagemagick/7.1.1-44... (809 files, 32.5MB)
Removing: /Users/valiha/Library/Caches/Homebrew/imagemagick_bottle_manifest--7.1.1-44... (94.9KB)
Removing: /Users/valiha/Library/Caches/Homebrew/imagemagick--7.1.1-44... (10.7MB)
==> Upgrading librsvg
  2.59.2 -> 2.60.0 
==> Installing dependencies for librsvg: gdk-pixbuf
==> Installing librsvg dependency: gdk-pixbuf
==> Downloading https://ghcr.io/v2/homebrew/core/gdk-pixbuf/manifests/2.42.12_1
Already downloaded: /Users/valiha/Library/Caches/Homebrew/downloads/2eeb910ea69bc28d9dc0b3b121819ff59ea92fa20bab68c59b6a7a7d5af0708b--gdk-pixbuf-2.42.12_1.bottle_manifest.json
==> Pouring gdk-pixbuf--2.42.12_1.arm64_sequoia.bottle.tar.gz
==> /opt/homebrew/Cellar/gdk-pixbuf/2.42.12_1/bin/gdk-pixbuf-query-loaders --update-cache
🍺  /opt/homebrew/Cellar/gdk-pixbuf/2.42.12_1: 152 files, 4.0MB
==> Installing librsvg
==> Pouring librsvg--2.60.0.arm64_sequoia.bottle.tar.gz
==> /opt/homebrew/opt/gdk-pixbuf/bin/gdk-pixbuf-query-loaders --update-cache
🍺  /opt/homebrew/Cellar/librsvg/2.60.0: 21 files, 21.2MB
==> Running `brew cleanup librsvg`...
Removing: /opt/homebrew/Cellar/librsvg/2.59.2... (21 files, 19.6MB)
Removing: /Users/valiha/Library/Caches/Homebrew/librsvg_bottle_manifest--2.59.2... (29.2KB)
Removing: /Users/valiha/Library/Caches/Homebrew/librsvg--2.59.2... (6.6MB)
==> Upgrading adwaita-icon-theme
  47.0 -> 48.0 
==> Pouring adwaita-icon-theme--48.0.all.bottle.tar.gz
🍺  /opt/homebrew/Cellar/adwaita-icon-theme/48.0: 828 files, 12.7MB
==> Running `brew cleanup adwaita-icon-theme`...
Removing: /opt/homebrew/Cellar/adwaita-icon-theme/47.0... (844 files, 11.3MB)
==> Upgrading libvirt
  11.1.0 -> 11.2.0 
==> Pouring libvirt--11.2.0.arm64_sequoia.bottle.tar.gz
==> Caveats
To restart libvirt after an upgrade:
  brew services restart libvirt
Or, if you don't want/need a background service you can just run:
  /opt/homebrew/opt/libvirt/sbin/libvirtd -f /opt/homebrew/etc/libvirt/libvirtd.conf
==> Summary
🍺  /opt/homebrew/Cellar/libvirt/11.2.0: 693 files, 46.9MB
==> Running `brew cleanup libvirt`...
Removing: /opt/homebrew/Cellar/libvirt/11.1.0... (693 files, 46.5MB)
Removing: /Users/valiha/Library/Caches/Homebrew/libvirt_bottle_manifest--11.1.0... (38.6KB)
Removing: /Users/valiha/Library/Caches/Homebrew/libvirt--11.1.0... (12.4MB)
==> Upgrading meson
  1.6.0 -> 1.7.2 
==> Pouring meson--1.7.2.all.bottle.tar.gz
🍺  /opt/homebrew/Cellar/meson/1.7.2: 259 files, 3.7MB
==> Running `brew cleanup meson`...
Removing: /opt/homebrew/Cellar/meson/1.6.0... (257 files, 3.7MB)
Removing: /Users/valiha/Library/Caches/Homebrew/meson_bottle_manifest--1.6.1... (3.5KB)
Removing: /Users/valiha/Library/Caches/Homebrew/meson_bottle_manifest--1.7.0... (3.5KB)
==> Upgrading netpbm
  11.02.12 -> 11.02.15 
==> Pouring netpbm--11.02.15.arm64_sequoia.bottle.tar.gz
🍺  /opt/homebrew/Cellar/netpbm/11.02.15: 825 files, 19.5MB
==> Running `brew cleanup netpbm`...
Removing: /opt/homebrew/Cellar/netpbm/11.02.11... (417 files, 18.7MB)
Removing: /opt/homebrew/Cellar/netpbm/11.02.12... (417 files, 18.7MB)
Removing: /Users/valiha/Library/Caches/Homebrew/netpbm_bottle_manifest--11.02.12... (44.1KB)
Removing: /Users/valiha/Library/Caches/Homebrew/netpbm_bottle_manifest--11.02.13... (44.1KB)
Removing: /Users/valiha/Library/Caches/Homebrew/netpbm--11.02.12... (1.7MB)
==> Upgrading numpy
  2.2.3 -> 2.2.5 
==> Installing dependencies for numpy: mpfr
==> Installing numpy dependency: mpfr
==> Downloading https://ghcr.io/v2/homebrew/core/mpfr/manifests/4.2.2
Already downloaded: /Users/valiha/Library/Caches/Homebrew/downloads/991b389ea6f1daa5dc48fd5250bcc5b85e827eb18b8ad4acd89419f2ace47d88--mpfr-4.2.2.bottle_manifest.json
==> Pouring mpfr--4.2.2.arm64_sequoia.bottle.tar.gz
🍺  /opt/homebrew/Cellar/mpfr/4.2.2: 31 files, 3.1MB
==> Installing numpy
==> Pouring numpy--2.2.5.arm64_sequoia.bottle.tar.gz
Error: The `brew link` step did not complete successfully
The formula built, but is not symlinked into /opt/homebrew
Could not symlink bin/f2py
Target /opt/homebrew/bin/f2py
already exists. You may want to remove it:
  rm '/opt/homebrew/bin/f2py'

To force the link and overwrite all conflicting files:
  brew link --overwrite numpy

To list all files that would be deleted:
  brew link --overwrite numpy --dry-run

Possible conflicting files are:
/opt/homebrew/bin/f2py
==> Summary
🍺  /opt/homebrew/Cellar/numpy/2.2.5: 1,755 files, 35.3MB
==> Running `brew cleanup numpy`...
Removing: /opt/homebrew/Cellar/numpy/2.2.3... (1,701 files, 35.0MB)
Removing: /Users/valiha/Library/Caches/Homebrew/numpy_bottle_manifest--2.2.3... (14.5KB)
Removing: /Users/valiha/Library/Caches/Homebrew/numpy--2.2.3... (8.8MB)
==> Upgrading py3cairo
  1.27.0_1 -> 1.28.0 
==> Pouring py3cairo--1.28.0.arm64_sequoia.bottle.tar.gz
🍺  /opt/homebrew/Cellar/py3cairo/1.28.0: 22 files, 1MB
==> Running `brew cleanup py3cairo`...
Removing: /opt/homebrew/Cellar/py3cairo/1.27.0_1... (30 files, 1.5MB)
==> Upgrading pygobject3
  3.50.0_1 -> 3.52.3 
==> Pouring pygobject3--3.52.3.arm64_sequoia.bottle.tar.gz
🍺  /opt/homebrew/Cellar/pygobject3/3.52.3: 70 files, 1.7MB
==> Running `brew cleanup pygobject3`...
Removing: /opt/homebrew/Cellar/pygobject3/3.50.0_1... (143 files, 3.1MB)
==> Upgrading gnuradio
  3.10.12.0 -> 3.10.12.0_1 
==> Installing dependencies for gnuradio: pmix, gsettings-desktop-schemas, rpds-py, spdlog and uhd
==> Installing gnuradio dependency: pmix
==> Downloading https://ghcr.io/v2/homebrew/core/pmix/manifests/5.0.7
Already downloaded: /Users/valiha/Library/Caches/Homebrew/downloads/df4a7bf3e46015b0eff41d50681af64af82df9a3833941ad972780d7436daad1--pmix-5.0.7.bottle_manifest.json
==> Pouring pmix--5.0.7.arm64_sequoia.bottle.tar.gz
🍺  /opt/homebrew/Cellar/pmix/5.0.7: 362 files, 8.8MB
==> Installing gnuradio dependency: gsettings-desktop-schemas
==> Downloading https://ghcr.io/v2/homebrew/core/gsettings-desktop-schemas/manifests/48.0
Already downloaded: /Users/valiha/Library/Caches/Homebrew/downloads/b50977acc6e572c3fef03f9e0d5a91fb31313e24dce8cea5c0cedcc626a07b3b--gsettings-desktop-schemas-48.0.bottle_manifest.json
==> Pouring gsettings-desktop-schemas--48.0.arm64_sequoia.bottle.tar.gz
==> /opt/homebrew/opt/glib/bin/glib-compile-schemas /opt/homebrew/share/glib-2.0/schemas
🍺  /opt/homebrew/Cellar/gsettings-desktop-schemas/48.0: 107 files, 5.5MB
==> Installing gnuradio dependency: rpds-py
==> Downloading https://ghcr.io/v2/homebrew/core/rpds-py/manifests/0.24.0
Already downloaded: /Users/valiha/Library/Caches/Homebrew/downloads/4cdd7e49f26a614cac11276cb28c6bfd1c0c673a75d8ec8db7fdadf63d50237c--rpds-py-0.24.0.bottle_manifest.json
==> Pouring rpds-py--0.24.0.arm64_sequoia.bottle.tar.gz
🍺  /opt/homebrew/Cellar/rpds-py/0.24.0: 23 files, 2.0MB
==> Installing gnuradio dependency: spdlog
==> Downloading https://ghcr.io/v2/homebrew/core/spdlog/manifests/1.15.2
Already downloaded: /Users/valiha/Library/Caches/Homebrew/downloads/166747e4d6e61e716221ae539971fb93c4f2204a59700c1803c05a4ab608ead1--spdlog-1.15.2.bottle_manifest.json
==> Pouring spdlog--1.15.2.arm64_sequoia.bottle.tar.gz
🍺  /opt/homebrew/Cellar/spdlog/1.15.2: 104 files, 1.5MB
==> Installing gnuradio dependency: uhd
==> Downloading https://ghcr.io/v2/homebrew/core/uhd/manifests/4.8.0.0_1
Already downloaded: /Users/valiha/Library/Caches/Homebrew/downloads/1fa414e4d81cc165453c8a6f063e090f67f2600b0f975aa60981a4b8ee85779b--uhd-4.8.0.0_1.bottle_manifest.json
==> Pouring uhd--4.8.0.0_1.arm64_sequoia.bottle.tar.gz
🍺  /opt/homebrew/Cellar/uhd/4.8.0.0_1: 2,331 files, 58.4MB
==> Installing gnuradio
==> Pouring gnuradio--3.10.12.0_1.arm64_sequoia.bottle.tar.gz
🍺  /opt/homebrew/Cellar/gnuradio/3.10.12.0_1: 3,142 files, 41.9MB
==> Running `brew cleanup gnuradio`...
Removing: /opt/homebrew/Cellar/gnuradio/3.10.12.0... (3,140 files, 42.8MB)
Removing: /Users/valiha/Library/Caches/Homebrew/gnuradio_bottle_manifest--3.10.12.0... (129.6KB)
Removing: /Users/valiha/Library/Caches/Homebrew/gnuradio--3.10.12.0... (10.4MB)
==> Upgrading poppler
  25.02.0 -> 25.04.0 
==> Installing dependencies for poppler: libassuan, gpgme and nss
==> Installing poppler dependency: libassuan
==> Downloading https://ghcr.io/v2/homebrew/core/libassuan/manifests/3.0.2
Already downloaded: /Users/valiha/Library/Caches/Homebrew/downloads/0fcd4af28064aef7277b774e3698e36630214907b803972d6722ec02a47a59cd--libassuan-3.0.2.bottle_manifest.json
==> Pouring libassuan--3.0.2.arm64_sequoia.bottle.tar.gz
🍺  /opt/homebrew/Cellar/libassuan/3.0.2: 18 files, 566.9KB
==> Installing poppler dependency: gpgme
==> Downloading https://ghcr.io/v2/homebrew/core/gpgme/manifests/1.24.2
Already downloaded: /Users/valiha/Library/Caches/Homebrew/downloads/b27e679213b6f16659cc6b431f4d7c29bc643a317e9878028545379b1cf08ec0--gpgme-1.24.2.bottle_manifest.json
==> Pouring gpgme--1.24.2.arm64_sequoia.bottle.tar.gz
🍺  /opt/homebrew/Cellar/gpgme/1.24.2: 110 files, 4.8MB
==> Installing poppler dependency: nss
==> Downloading https://ghcr.io/v2/homebrew/core/nss/manifests/3.110
Already downloaded: /Users/valiha/Library/Caches/Homebrew/downloads/d477f4ddc6ff798f5fd4d04a17dcb526f34acd4976ecbb61279f5f8a14617d98--nss-3.110.bottle_manifest.json
==> Pouring nss--3.110.arm64_sequoia.bottle.tar.gz
🍺  /opt/homebrew/Cellar/nss/3.110: 216 files, 19.6MB
==> Installing poppler
==> Pouring poppler--25.04.0.arm64_sequoia.bottle.tar.gz
🍺  /opt/homebrew/Cellar/poppler/25.04.0: 443 files, 30MB
==> Running `brew cleanup poppler`...
Removing: /opt/homebrew/Cellar/poppler/25.02.0... (443 files, 30.0MB)
Removing: /Users/valiha/Library/Caches/Homebrew/poppler_bottle_manifest--25.02.0... (48.0KB)
Removing: /Users/valiha/Library/Caches/Homebrew/poppler--25.02.0... (9MB)
==> Upgrading pyqt
  6.8.1 -> 6.9.0 
==> Pouring pyqt--6.9.0.arm64_sonoma.bottle.tar.gz
🍺  /opt/homebrew/Cellar/pyqt/6.9.0: 1,262 files, 37.1MB
==> Running `brew cleanup pyqt`...
Removing: /opt/homebrew/Cellar/pyqt/6.8.1... (1,256 files, 36.9MB)
Removing: /Users/valiha/Library/Caches/Homebrew/pyqt_bottle_manifest--6.8.1... (54KB)
Removing: /Users/valiha/Library/Caches/Homebrew/pyqt--6.8.1... (6.6MB)
==> Upgrading python@3.10
  3.10.15 -> 3.10.17 
==> Installing dependencies for python@3.10: gdbm
==> Installing python@3.10 dependency: gdbm
==> Downloading https://ghcr.io/v2/homebrew/core/gdbm/manifests/1.25
Already downloaded: /Users/valiha/Library/Caches/Homebrew/downloads/f1c1f4352b188ebc1592502d286d9908ea4442531a049d3be8d09db70ddec107--gdbm-1.25.bottle_manifest.json
==> Pouring gdbm--1.25.arm64_sequoia.bottle.tar.gz
🍺  /opt/homebrew/Cellar/gdbm/1.25: 25 files, 1MB
==> Installing python@3.10
==> Pouring python@3.10--3.10.17.arm64_sequoia.bottle.tar.gz
==> /opt/homebrew/Cellar/python@3.10/3.10.17/bin/python3.10 -Im ensurepip
==> /opt/homebrew/Cellar/python@3.10/3.10.17/bin/python3.10 -Im pip install -v --no-index --upgrade --isolated --target=/opt/homebrew/lib/python3.10/site-packages /opt/homebrew/Cellar/pyt
==> Caveats
Python is installed as
  /opt/homebrew/bin/python3.10

Unversioned and major-versioned symlinks `python`, `python3`, `python-config`, `python3-config`, `pip`, `pip3`, etc. pointing to
`python3.10`, `python3.10-config`, `pip3.10` etc., respectively, are installed into
  /opt/homebrew/opt/python@3.10/libexec/bin

You can install Python packages with
  pip3.10 install <package>
They will install into the site-package directory
  /opt/homebrew/lib/python3.10/site-packages

tkinter is no longer included with this formula, but it is available separately:
  brew install python-tk@3.10

If you do not need a specific version of Python, and always want Homebrew's `python3` in your PATH:
  brew install python3

See: https://docs.brew.sh/Homebrew-and-Python
==> Summary
🍺  /opt/homebrew/Cellar/python@3.10/3.10.17: 3,081 files, 56.7MB
==> Running `brew cleanup python@3.10`...
Removing: /opt/homebrew/Cellar/python@3.10/3.10.15... (3,182 files, 58.5MB)
==> Upgrading qemu
  9.2.2 -> 10.0.0 
==> Installing dependencies for qemu: capstone
==> Installing qemu dependency: capstone
==> Downloading https://ghcr.io/v2/homebrew/core/capstone/manifests/5.0.5
Already downloaded: /Users/valiha/Library/Caches/Homebrew/downloads/c0c0dfcac152442240eb9c849b2694a9d2d35ce93b92e701037188322abc8b6c--capstone-5.0.5.bottle_manifest.json
==> Pouring capstone--5.0.5.arm64_sequoia.bottle.tar.gz
🍺  /opt/homebrew/Cellar/capstone/5.0.5: 31 files, 22.4MB
==> Installing qemu
==> Pouring qemu--10.0.0.arm64_sequoia.bottle.tar.gz
🍺  /opt/homebrew/Cellar/qemu/10.0.0: 169 files, 681.8MB
==> Running `brew cleanup qemu`...
Removing: /opt/homebrew/Cellar/qemu/9.2.2... (167 files, 669.5MB)
Removing: /Users/valiha/Library/Caches/Homebrew/qemu_bottle_manifest--9.2.2... (46KB)
Removing: /Users/valiha/Library/Caches/Homebrew/qemu--9.2.2... (103.4MB)
==> Upgrading suite-sparse
  7.8.3 -> 7.10.2 
==> Pouring suite-sparse--7.10.2.arm64_sequoia.bottle.tar.gz
🍺  /opt/homebrew/Cellar/suite-sparse/7.10.2: 217 files, 49.3MB
==> Running `brew cleanup suite-sparse`...
Removing: /opt/homebrew/Cellar/suite-sparse/7.8.3... (217 files, 116.5MB)
Removing: /Users/valiha/Library/Caches/Homebrew/suite-sparse_bottle_manifest--7.10.0... (19.2KB)
==> Upgrading sundials
  7.2.1 -> 7.3.0 
==> Pouring sundials--7.3.0.arm64_sequoia.bottle.tar.gz
🍺  /opt/homebrew/Cellar/sundials/7.3.0: 227 files, 6.6MB
==> Running `brew cleanup sundials`...
Removing: /opt/homebrew/Cellar/sundials/7.2.1... (222 files, 6.5MB)
Removing: /Users/valiha/Library/Caches/Homebrew/sundials_bottle_manifest--7.2.1... (21KB)
Removing: /Users/valiha/Library/Caches/Homebrew/sundials--7.2.1... (1.6MB)
==> Upgrading texlive
  20240312_3 -> 20250308_1 
==> Installing dependencies for texlive: luajit, openjdk and perl
==> Installing texlive dependency: luajit
==> Downloading https://ghcr.io/v2/homebrew/core/luajit/manifests/2.1.1744318430
Already downloaded: /Users/valiha/Library/Caches/Homebrew/downloads/4619073f105713f38f3e81ead88ae254efde33403ae1c697893e0d40f27385ca--luajit-2.1.1744318430.bottle_manifest.json
==> Pouring luajit--2.1.1744318430.arm64_sequoia.bottle.tar.gz
🍺  /opt/homebrew/Cellar/luajit/2.1.1744318430: 56 files, 2.1MB
==> Installing texlive dependency: openjdk
==> Downloading https://ghcr.io/v2/homebrew/core/openjdk/manifests/23.0.2
Already downloaded: /Users/valiha/Library/Caches/Homebrew/downloads/8dea1e6c16fdb5358c4865d24639ab139310acfcd2a8472a89f458bbb046eac5--openjdk-23.0.2.bottle_manifest.json
==> Pouring openjdk--23.0.2.arm64_sequoia.bottle.tar.gz
🍺  /opt/homebrew/Cellar/openjdk/23.0.2: 602 files, 337.4MB
==> Installing texlive dependency: perl
==> Downloading https://ghcr.io/v2/homebrew/core/perl/manifests/5.40.2
Already downloaded: /Users/valiha/Library/Caches/Homebrew/downloads/a520d519d4450ead392eb1a07673c5147af1d7fbc5977a0acf622bddeb1ecbd5--perl-5.40.2.bottle_manifest.json
==> Pouring perl--5.40.2.arm64_sequoia.bottle.tar.gz
🍺  /opt/homebrew/Cellar/perl/5.40.2: 2,785 files, 69.8MB
==> Installing texlive
==> Pouring texlive--20250308_1.arm64_sequoia.bottle.tar.gz
🍺  /opt/homebrew/Cellar/texlive/20250308_1: 189,663 files, 4GB
==> Running `brew cleanup texlive`...
Removing: /opt/homebrew/Cellar/texlive/20240312_3... (188,975 files, 4.2GB)
==> Upgrading wireshark
  4.4.5 -> 4.4.6 
==> Installing dependencies for wireshark: c-ares, libgpg-error and libnghttp3
==> Installing wireshark dependency: c-ares
==> Downloading https://ghcr.io/v2/homebrew/core/c-ares/manifests/1.34.5
Already downloaded: /Users/valiha/Library/Caches/Homebrew/downloads/b32385f129da9bb17ff5fb7c5648afecc97403ff74cb72a32eb6ca08741744b6--c-ares-1.34.5.bottle_manifest.json
==> Pouring c-ares--1.34.5.arm64_sequoia.bottle.tar.gz
🍺  /opt/homebrew/Cellar/c-ares/1.34.5: 176 files, 1MB
==> Installing wireshark dependency: libgpg-error
==> Downloading https://ghcr.io/v2/homebrew/core/libgpg-error/manifests/1.55
Already downloaded: /Users/valiha/Library/Caches/Homebrew/downloads/2c5d602f2d26432221cd72fce331fa0f1a3f094b652003c760d3cb1f2a9f53de--libgpg-error-1.55.bottle_manifest.json
==> Pouring libgpg-error--1.55.arm64_sequoia.bottle.tar.gz
🍺  /opt/homebrew/Cellar/libgpg-error/1.55: 50 files, 1.8MB
==> Installing wireshark dependency: libnghttp3
==> Downloading https://ghcr.io/v2/homebrew/core/libnghttp3/manifests/1.9.0
Already downloaded: /Users/valiha/Library/Caches/Homebrew/downloads/7237d5d6d78945949a09a7cb0b93c3126a471007e6aa9e0c0183184002696fba--libnghttp3-1.9.0.bottle_manifest.json
==> Pouring libnghttp3--1.9.0.arm64_sequoia.bottle.tar.gz
🍺  /opt/homebrew/Cellar/libnghttp3/1.9.0: 19 files, 559.6KB
==> Installing wireshark
==> Pouring wireshark--4.4.6.arm64_sequoia.bottle.tar.gz
==> Caveats
This formula only installs the command-line utilities by default.

Install Wireshark.app with Homebrew Cask:
  brew install --cask wireshark

If your list of available capture interfaces is empty
(default macOS behavior), install ChmodBPF:
  brew install --cask wireshark-chmodbpf
==> Summary
🍺  /opt/homebrew/Cellar/wireshark/4.4.6: 1,028 files, 109.7MB
==> Running `brew cleanup wireshark`...
Removing: /opt/homebrew/Cellar/wireshark/4.4.5... (1,028 files, 109.6MB)
Removing: /Users/valiha/Library/Caches/Homebrew/wireshark_bottle_manifest--4.4.5... (28KB)
Removing: /Users/valiha/Library/Caches/Homebrew/wireshark--4.4.5... (25.7MB)
==> Checking for dependents of upgraded formulae...
==> No broken dependents found!
==> Caveats
==> llvm
CLANG_CONFIG_FILE_SYSTEM_DIR: /opt/homebrew/etc/clang
CLANG_CONFIG_FILE_USER_DIR:   ~/.config/clang

LLD is now provided in a separate formula:
  brew install lld

Using `clang`, `clang++`, etc., requires a CLT installation at `/Library/Developer/CommandLineTools`.
If you don't want to install the CLT, you can write appropriate configuration files pointing to your
SDK at ~/.config/clang.

To use the bundled libunwind please use the following LDFLAGS:
  LDFLAGS="-L/opt/homebrew/opt/llvm/lib/unwind -lunwind"

To use the bundled libc++ please use the following LDFLAGS:
  LDFLAGS="-L/opt/homebrew/opt/llvm/lib/c++ -L/opt/homebrew/opt/llvm/lib/unwind -lunwind"

NOTE: You probably want to use the libunwind and libc++ provided by macOS unless you know what you're doing.

llvm is keg-only, which means it was not symlinked into /opt/homebrew,
because macOS already provides this software and installing another version in
parallel can cause all kinds of trouble.

If you need to have llvm first in your PATH, run:
  echo 'export PATH="/opt/homebrew/opt/llvm/bin:$PATH"' >> ~/.zshrc

For compilers to find llvm you may need to set:
  export LDFLAGS="-L/opt/homebrew/opt/llvm/lib"
  export CPPFLAGS="-I/opt/homebrew/opt/llvm/include"
==> ccache
To install symlinks for compilers that will automatically use
ccache, prepend this directory to your PATH:
  /opt/homebrew/opt/ccache/libexec

If this is an upgrade and you have previously added the symlinks to
your PATH, you may need to modify it to the path specified above so
it points to the current version.

NOTE: ccache can prevent some software from compiling.
ALSO NOTE: The brew command, by design, will never use ccache.
==> tesseract
This formula contains only the "eng", "osd", and "snum" language data files.
If you need any other supported languages, run `brew install tesseract-lang`.
==> imagemagick
Ghostscript is not installed by default as a dependency.
If you need PS or PDF support, ImageMagick will still use the ghostscript formula if installed directly.
==> libvirt
To restart libvirt after an upgrade:
  brew services restart libvirt
Or, if you don't want/need a background service you can just run:
  /opt/homebrew/opt/libvirt/sbin/libvirtd -f /opt/homebrew/etc/libvirt/libvirtd.conf
==> python@3.10
Python is installed as
  /opt/homebrew/bin/python3.10

Unversioned and major-versioned symlinks `python`, `python3`, `python-config`, `python3-config`, `pip`, `pip3`, etc. pointing to
`python3.10`, `python3.10-config`, `pip3.10` etc., respectively, are installed into
  /opt/homebrew/opt/python@3.10/libexec/bin

You can install Python packages with
  pip3.10 install <package>
They will install into the site-package directory
  /opt/homebrew/lib/python3.10/site-packages

tkinter is no longer included with this formula, but it is available separately:
  brew install python-tk@3.10

If you do not need a specific version of Python, and always want Homebrew's `python3` in your PATH:
  brew install python3

See: https://docs.brew.sh/Homebrew-and-Python
==> wireshark
This formula only installs the command-line utilities by default.

Install Wireshark.app with Homebrew Cask:
  brew install --cask wireshark

If your list of available capture interfaces is empty
(default macOS behavior), install ChmodBPF:
  brew install --cask wireshark-chmodbpf
```

# References

- [ ] [Installing the Open Source FPGA tool chain on Mac](https://datacore.nanographs.io/000+Publish/Installing+the+Open+Source+FPGA+tool+chain+on+Mac)
