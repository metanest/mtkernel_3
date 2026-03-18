# μT-Kernel 3.0 RISC-V移植版
(まだ)作業中です。Sifive HiFive1 Rev B で動きます。この移植版についての問合せ等はきしもとまでお願いします。その他の RISC-V ボードへの対応は、ボードの現物支給と ￥開発資金￥ の提供があればやろうと思います。

masterブランチではなくdevelopブランチへの差分となります。

## FreeBSD でのビルド手順
コンパイラ devel/riscv32-unknown-elf-gcc をインストールします。

    $ sudo pkg install riscv32-unknown-elf-gcc

リポジトリをクローンします。

    $ git clone https://github.com/metanest/mtkernel_3.git

サンプルアプリを実装したブランチ mysample ( https://github.com/metanest/mtkernel_3/tree/mysample ) をチェックアウトします。

    $ cd mtkernel_3
    $ git checkout remotes/origin/mysample
    $ git switch -c mysample

ビルドディレクトリに移動しビルドします。

    $ cd build_make
	$ gmake all

build_make ディレクトリに mtkernel_3.elf が生成されているはずです。

SiFive HiFive1 Rev B を USB に接続します。

(別ウィンドウで) SiFive HiFive1 Rev B のシリアル出力をモニタします。

    $ sudo cu -s 115200 -l /dev/ttyU0

書き込みには devel/openocd を使うのでインストールします。

    $ sudo pkg install openocd

作業用ディレクトリを作り、そこに次のような設定ファイルを作ります。

    $ cat openocd.cfg
    source [find board/sifive-hifive1-revb.cfg]
    
    init
    
    proc flash_elf {elf_file} {
        reset
        halt
        flash write_image erase $elf_file
        verify_image $elf_file
        echo "flash write_image ($elf_file) complete"
        reset
        exit
    }

さきほどのビルドでできた mtkernel_3.elf をコピーしてきて、次のようなコマンドで SiFive HiFive1 Rev B に書き込みます。

    $ sudo openocd -f openocd.cfg -c 'flash_elf "mtkernel_3.elf"'

書き込みが終了したら、自動でリセットされるはずですがうまくいかない場合は手動でリセットすれば、動き始めるはずです。

## Linux でのビルド手順
SiFive が配布しているツールチェインを使います。 https://github.com/sifive/freedom-tools/releases からリンクされている riscv64-unknown-elf-toolchain-10.2.0-2020.12.8-x86_64-linux-centos6.tar.gz をダウンロードしてください（Red Hat系の場合。Debian系の場合は該当部を ubuntu14 に読み替えてください）。

    $ wget https://static.dev.sifive.com/dev-tools/freedom-tools/v2020.12/riscv64-unknown-elf-toolchain-10.2.0-2020.12.8-x86_64-linux-centos6.tar.gz

$HOME に展開します

    $ cd $HOME
	$ tar xf (ファイルを置いた場所)/riscv64-unknown-elf-toolchain-10.2.0-2020.12.8-x86_64-linux-centos6.tar.gz

名前があまりに長いので tools に変えます。既に tools というディレクトリがある人は適宜別名に置き換えるか、既にあるほうを別の名前に mv してください。

    $ mv riscv64-unknown-elf-toolchain-10.2.0-2020.12.8-x86_64-linux-centos6 tools

リポジトリのクローンと mysample のチェックアウトは FreeBSD の場合と同じです。

次に build_make/makefile と build_make/sifive_hifive1_revb.mk を修正します。

makefile は OBJS += -lgcc という記述を削除してください。

sifive_hifive1_revb.mk は、最初のほうにある GCC と AS と LINK の設定を riscv32-... から riscv64-... に変更してください。さきほどの SiFive のツールチェインで提供されているのが 64 ビット対応版だからです。-mcpu=sifive-e31 という引数により、32 ビットコードが生成されますので安心してください。

以上の修正ができたらメイクできます。ツールにパスを通して make を起動します。Linux では標準で GNU Make でしょう。

    $ cd build_make
    $ PATH=$HOME/tools/bin:$PATH make all

SiFive HiFive1 Rev B を USB に接続します。

(別ウィンドウで) SiFive HiFive1 Rev B のシリアル出力をモニタします。デバイス名はシステムに依り違うかもしれません。私の環境は Fedora です。

    $ sudo dnf install cu # cu がインストールされてなかったらインストールする
    $ sudo cu -s 115200 -l /dev/ttyACM0

書き込みには FreeBSD 同様に openocd を使うのでインストールします。

    $ sudo dnf install openocd

あとは FreeBSD と同様の openocd.cfg というファイルを用意して、

    $ sudo openocd -f openocd.cfg -c 'flash_elf "mtkernel_3.elf"'

とすれば書き込みできて動かせるはずです。
# μT-Kernel 3.0
μT-Kernel 3.0 is a Real-time OS for Small-scale Embedded Systems and IoT Edge nodes.

- It is compliant with IEEE Standard 2050-2018 and has high compatibility with μT-Kernel 2.0.
- Its source code has been reviewed and rewritten so that porting to latest microprocessors has become easier.
- It is not tied to particular development environment, and is usable with many such environments.

μT-Kernel3.0 is developed by TRON Forum.
Its source code is released as open source under the condition of T-License2.2.

See below for T-License 2.2.

	/docs/TEF000-219-200401.pdf

Please see below for documents such as implementation specifications.

[μT-Kernel 3.0 documents](https://tron-forum.github.io/mtkernel_3/)  

The projects for BSP (Board Support Package) and various development environments are published below.

[μT-Kernel 3.0 BSP2(Board Support Package) v2](https://github.com/tron-forum/mtk3_bsp2)  
[μT-Kernel 3.0 BSP (Board Support Package)](https://github.com/tron-forum/mtk3_bsp)  
[μT-Kernel 3.0 Development environment collection](https://github.com/tron-forum/mtk3_devenv)  

For inquiries to TRON Forum, visit the following website

[TRON Forum  (https://www.tron.org)](https://www.tron.org)

---
μT-Kernel 3.0は、小規模な組込みシステムおよびIoTエッジノード向けのリアルタイムOSです。

- IEEE 2050-2018規格に準拠し、かつ、μT-Kernel 2.0と高い互換性を維持しています。
- ソースコードの全面見直しにより、最新のマイコンへの移植性が高まりました。
- 特定の開発ツールに依存せず、様々な開発環境で使用できます。

μT-Kernel 3.0はトロンフォーラムが開発しています。
μT-Kernel 3.0のソースコードはT-License2.2に基づきオープンソースとして公開されています。

T-License2.2の内容は以下をご覧ください。

	/docs/TEF000-219-200401.pdf

実装仕様書などのドキュメントは以下をご覧ください。

[μT-Kernel 3.0 documents](https://tron-forum.github.io/mtkernel_3/)  


BSP(ボードサポートパッケージ)、各種開発環境向けのプロジェクトは以下に公開しています。

[μT-Kernel 3.0 BSP2(Board Support Package) v2](https://github.com/tron-forum/mtk3_bsp2)  
[μT-Kernel 3.0 BSP (Board Support Package)](https://github.com/tron-forum/mtk3_bsp)  
[μT-Kernel 3.0 Development environment collection](https://github.com/tron-forum/mtk3_devenv)  

トロンフォーラムへのお問い合わせは以下のWebサイトへ

[トロンフォーラム  (https://www.tron.org)](https://www.tron.org)
