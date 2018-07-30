= JSPソルバでタスク管理...したい
@<author>{かふぇした}
//profile{
    ねぇ無理無理！（社会人）
//}

//lead{
    いやーキツいっす（社会人）
//}

== この記事のやりたいこと
  * @<b>{ジョブショップスケジューリング問題について解説します．}
  * @<b>{以上です．}

猛暑@<fn>{mosho}の中，皆さんはいかがお過ごしでしょうか．
私は今年から社会人になり，タスク管理の重要性を痛感しているところです．
//footnote[mosho][2018年8月現在]

タスク管理を定式化した組合せ最適化問題として，@<b>{スケジューリング問題}があげられます．
スケジューリング問題のなかでも，最も実用の例に近いとされる
@<b>{ジョブショップスケジューリング問題 (JSP; Job-shop Scheduling Problem)}は，
古くから研究の対象とされてきました．
JSPは，また，定義が単純かつ分かりやすい一方，厳密解法が判明していない困難な問題でもあるため，
@<b>{皆さん大好き巡回セールスマン問題}と共に，近似解法のベンチマークとしても広く利用されています．

今回は，JSPを含めたスケジューリング問題，およびその解法についてざぁっと説明します．
実装によるベンチマークは行いません@<fn>{zikan}．お兄さん許して！
//footnote[zikan][圧倒的に時間と気力が足りない]

== スケジューリング問題
スケジューリング問題は，処理されるべき@<b>{仕事}と，それを処理する@<b>{機械}によって構成されます．
仕事と機械はそれぞれ複数個存在し，各仕事は複数の機械によって処理されます．
@<img>{schedule}に，この状況を示します．
この例では，各仕事が機械A，機械B，機械Cの順で処理されます．
例えるなら，複数の鉄鋼品の製造（仕事A～C）を鋳造（機械A），圧延（機械B），加工（機械C）によって処理するようなイメージでしょうか．

//image[schedule][3機械3仕事のスケジューリング問題の例][scale=1.0]

原則として，機械は，同時に複数の仕事を処理することはできません．また，仕事は，同時に複数の機械に処理されることはできません．
これらの制約を満たしたうえで，@<img>{schedule}の各仕事を処理する例を@<img>{make1}に示します．
機械と仕事が入れ替わっていることに注意してください．

//image[make1][@<img>{schedule}におけるガントチャートの例][scale=1.0]

@<img>{make1}のように，縦軸に機械を取り，各機械が処理する仕事を時系列順に並べた図を@<b>{ガントチャート}と呼びます．
また，最初の仕事の開始時点（@<img>{make1}では機械Aが仕事Aの処理を開始する時点）から，最後の仕事の終了時点（@<img>{make1}では機械Bが仕事Cの処理を終了する時点）までの時間を@<b>{メイクスパン}
と呼びます．
