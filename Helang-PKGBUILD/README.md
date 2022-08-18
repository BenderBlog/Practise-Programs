# Helang-PKGBUILD
现在连个高中生都能自己创造语言了，时代变了，我这都要大三了连个小程序都写不出:-P  
现在已经上传到 AUR 了，在 aurhelper 中输入 `python-helang-git` 进行搜索即可安装。注意，这玩意依赖 `pyside6`。

## 原理
翻译自 [ArchWiki 中打包 Python 包文档](https://wiki.archlinux.org/title/Python_package_guidelines#Standards_based_(PEP_517))

......前面省略

### 安装方法->依照标准的方法 (PEP 517)

一个标准的打包方式是很直接的：使用 `python-wheel` 打包出 wheel ，然后通过 `python-installer` 安装到 `	$pkgdir`.

```
makedepends=(python-build python-installer python-wheel)

build() {
    cd "$_name-$pkgver"
    python -m build --wheel --no-isolation
}

package() {
    cd "$_name-$pkgver"
    python -m installer --destdir="$pkgdir" dist/*.whl
}
```

其中：
* `--wheel` 最终只会生成 wheel 文件，不会生成要分发的源代码文件
* `--no-isolation` 表示这个包是使用系统安装好的库(包括你在 `depends` 数组中定义的)。在默认情况下，这个工具会创建一个隔离系统的虚拟环境，然后在那里安装。
* `--destdir="$pkgdir"` 将文件安装到 `$pkgdir` 中，而不是宿主系统中，这样能避免权限错误。
* 你可以向 `installer` 传参 `--compile-bytecode=...` 或者 `--no-compile-bytecode`。不过默认情况下，程序自己知道该咋办，所以咱就不要瞎掺和了。

**警告:** 相较于使用源码构建软件包，跳过 `build` 而直接把 `.whl` 文件放在 `source` 数组中 (也就是直接使用预先编译好的直接解包安装) 是十分不推荐的。除非前面的选项不可行（比如说，作者**只**放出来 wheel 包，所以源代码构建不可行），千万不要这么干。

## 所以何某呢？
我们学校随便拿出来一个都比他强的多！