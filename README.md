# 「サイゼリヤで1000円あれば最大何kcal摂れるのか」をモンテカルロ法で解いてみる

[![MIT License](http://img.shields.io/badge/license-MIT-blue.svg?style=flat)](LICENSE)

## はじめに

これは以下の記事に触発されて書いたコードです。

* [「サイゼリヤで1000円あれば最大何kcal摂れるのか」を量子アニーリング計算(Wildqat)で解いてみた。](https://qiita.com/hodaka0714/items/cf44b4ece992a39b5be4)
* [「サイゼリヤで1000円あれば最大何kcal摂れるのか」をSMTソルバー(Z3)で解いてみた。](https://qiita.com/tanakh/items/a1fb13f78e0576415de3)

## 使い方

    python db2txt.py
    make
    ./a.out

## 出力

    $ ./a.out
    585
    959
    1494
    1527
    1710
    1730
    1820
    1826
    1854
    1940
    ポテトのグリル:366 kcal 199Yen
    アーリオ・オーリオ(Wサイズ):1120 kcal 574Yen
    ラージライス:454 kcal 219Yen
    合計 1940 kcal 992 Yen

## 解説

カロリーをエネルギーだと思って、普通のマルコフ連鎖モンテカルロを実行しています。1000円を超える試行は禁止しています。それだけです。