= タンパク質で見るデレマス次世代ママ候補初級編
@<author>{itezaP}
//profile{
闇の博士課程に進学しました。

こじらせてしまい、初めて抱き枕カバーを買ってしまいました。

大垣ひなたちゃん可愛いです。
//}

//lead{
先日「いちごは意外とバラに近い」という記事を見ました。

これは、ありすママということでしょうか。
//}

== はじめに （真面目なこと）
先日、論文誌Natureにて「The Rosa genome provides new insights into the domestication of modern roses」
という論文が掲載されました。
バラの遺伝子を解析し、他の遺伝子 （いちご、りんご）などと比較した結果、進化的にバラといちごは「思っていた以上に近い」ことが
わかったそうです@<fn>{rose}。
//footnote[rose][@<href>{https://www.nature.com/articles/s41588-018-0110-3}]

遺伝子単位で近いなら、そこから翻訳されるタンパク質単位ではどのくらい近いのか、と考えました。
そこで今回は、タンパク質のアミノ酸配列データ （以下、タンパク質配列）を用いて、バラといちごがどれくらい類似しているのか調査します。
さらに追加で、いくつかの生物種とバラの類似度を計算して比較を行いたいと思います。

これは学術的に興味があっただけです。
やましい心はありません。
本当です。

== はじめに （本当のこと）
先ほどの論文を眺めていて、ふとあることを考えました。
バラといえば、我らが母、櫻井桃華です。
いちごといえば、橘こと、橘ありすです。
両名は「アイドルマスターシンデレラガールズ （以下、デレマス）」に登場する、大変素敵で魅力的な女性たちです。
さらにデレマスのカップリングには「ももあり （桃華×ありす）」という素晴らしい組み合わせがあります。
いちごはバラに近い、ありすは桃華に近い、なるほどありすにバブみを感じるのか、なんて妄想を思いついたのがきっかけです。

さらにデレマスには、花や果物から連想できる女性たちが数人います。
ひまわりといえば龍崎薫、ライラックといえば相葉夕美、といった感じです。
例えばひまわりがバラに近ければ、「ももかお （桃華×薫）」という意外な可能性や、薫は母になってくれる女性である可能性が微レ存、
といった妄想も膨らみます。

== 類似度の決め方
物と物がどれくらい類似しているかを定量的に計算・解析することは、非常に重要ですが難しい問題です。
@<img>{alstroemeria}は「アイドルマスターシャイニーカラーズ」に登場する双子アイドル「大崎甜花、大崎甘奈」です。
双子なので容姿などが似ていることが見て取れますが、どれくらい類似しているかを定量的に表現するのは難しいです。
類似度を計算しようと思うと、様々な特徴をなんとか数値化して比較する方法が考えられます。
例えば色合いや全体の輪郭、喋る言葉や単語の傾向など様々あります。

//image[alstroemeria][甜花ちゃんが好きです][scale=0.95]

タンパク質の場合、同じ生物学的機能や立体構造を持っているかなどを予測するための重要な指標になります。
タンパク質配列同士の類似度を計算する方法として、生物学的な意味も考慮した配列アライメントによるアライメントスコアを求めるのが基本です。
ですが、今回は文書の類似度計算でよく用いられているn-gramを使って類似度を調査したいと思います。
n-gramは文字列や文書をn個の文字 （または単語）で分割する方法です。
例えば「櫻井桃華」を「2文字 (n=2)かつ1文字ずつスライド」で分割すると「櫻井、井桃、桃華」となります。
非常にシンプルな方法のため、様々な場面で応用することができます。
今回はn-gramをタンパク質配列の類似度に応用してみようと思います。
ある生物種のタンパク質配列すべてをn-gram （アミノ酸残基n文字単位）で分割し、その分割文字列群を各集合・ベクトルとします。
例えば「ARISU」というタンパク質配列があり「2文字 (n=2)かつ1文字ずつスライド」の場合、「AR、RI、IS、SU」となります。
ベクトルの大きさはその分割文字列の出現回数としました。

2つの集合・ベクトルを比較して類似度を求める指標は数多くあります。
今回、集合の類似度の指標としてJaccard係数、Dice係数、Simpson係数、Tanimoto係数を使用します。
各係数の導出方法は以下の通りです。
各式の@<m>{A,B}は任意の集合であり、@<m>{|A|,|B|}は各集合@<m>{A,B}の要素数を表します。

//texequation{
Jaccard(A,B) = \frac{|A \cap B|}{|A \cup B|}
//}

//texequation{
Dice(A,B) = \frac{2|A \cap B|}{|A| \cup |B|}
//}

//texequation{
Simpson(A,B) = \frac{|A \cap B|}{\mathrm{min}\{|A|,|B|\}}
//}

//texequation{
Tanimoto(A,B) = \frac{|A \cap B|}{|A|+|B|-|A \cap B|}
//}

ベクトルの類似度の指標としてはcos （コサイン）類似度を使用します。
cos類似度の計算式は以下の通りです。
@<m>{|V|}はベクトルの次元数を表します。

//texequation{
cos(\vec{A},\vec{B}) = \frac{\sum_{i=1}^{|V|}A_iB_i}{\sqrt{\sum_{i=1}^{|V|}A_i^2}\sqrt{\sum_{i=1}^{|V|}B_i^2}}
//}

== データセット
バラやいちごなどのタンパク質配列を集めます。
今回はアミノ酸配列データベースUniProt@<fn>{uniprot}から、学名で一致するデータをすべてダウンロードします。
//footnote[uniprot][@<href>{https://www.uniprot.org/}]
バラの場合「Rosa」で検索してヒットした配列をすべて対象とします。
登録されているバラはさらに細分化されて分類されているのですが、よくわからないので全て対象にしてしまいます。
今回集めた生物種と学名、データ数を@<table>{dataset}に示します。
さらにその花または果物から連想できるデレマスのアイドル名とその理由を示します。
加えて@<table>{dataset}に載っているアイドルのイラストを@<img>{charalist}に示します。

//tabooular[dataset][使用した生物種データ一覧]{
生物種名	|	学名	&	データ数	&	アイドル名 （理由）
==========>|====&====&====
バラ	|	Rosa	|	46,862	|	櫻井桃華 （ソロ曲、イラストより）
いちご	|	Fragaria Ananassa	|	769	|	橘ありす (好物より)
ひまわり	|	Helianthus Annuus	|	54,266	|	龍崎薫 （イラストより）
りんご	|	Malus Domestica	|	2,472	|	十時愛梨 （ソロ曲より）
クローバー	|	Trifolium Repens	|	372	|	緒方智絵里 （趣味より）
さくら	|	Prunus Yedoensis	|	142	|	小早川紗枝 （イラストより）
ライラック	|	Syringa Vulgaris	|	151	|	相葉夕美 （ソロ曲より）
ゆず	|	Citrus Junos	|	19	|	喜多見柚 （名前より）
//}

//image[charalist][アイドルのイラスト一覧][scale=0.95]

== 誰がもっとも桃華に近いのか
n-gram (n=2,3,4,5)によって生成された各生物種の集合を対象として、各指標でバラとの類似度を計算しました。
類似度が1に近い順で順位付けした結果を@<table>{set-result}に示します。
なお、学名・生物種名は長いので以後はアイドルの名前で表記します。
名前の下には類似度を示します。
類似度は小数点第3位で四捨五入しました。

//tabooular[set-result][集合の類似度]{
  順位 (n=2)	|	1	&	2	&	3	&	4	&	5	&	6	&	7
  ==========>|====&====&====&====&====&====&====
 Jaccard \ |	ありす	&	愛梨	&	智絵里	&	薫	&	紗枝	&	夕美	&	柚
      |	0.98	&	0.97	&	0.96	&	0.95	&	0.94	&	0.92	&	0.91
 Dice \ |	ありす	&	愛梨	&	智絵里	&	薫	&	紗枝	&	夕美	&	柚
      |	0.99	&	0.99	&	0.98	&	0.98	&	0.97	&	0.96	&	0.95
 Simpson \ |	柚	&	薫	&	愛梨	&	紗枝	&	夕美	&	ありす	&	智絵里
      |	1.0	&	1.0	&	1.0	&	0.99	&	0.99	&	0.99	&	0.99
 Tanimoto \ |	ありす	&	愛梨	&	智絵里	&	薫	&	紗枝	&	夕美	&	柚
      |	0.98	&	0.97	&	0.96	&	0.95	&	0.94	&	0.92	&	0.91
  --------------------------------------------------------------------
  > 順位 (n=3) <|	1	&	2	&	3	&	4	&	5	&	6	&	7
  --------------------------------------------------------------------
Jaccard \ |	ありす	&	愛梨	&	智絵里	&	薫	&	夕美	&	紗枝	&	柚
     |	0.96	&	0.95	&	0.94	&	0.92	&	0.84	&	0.79	&	0.43
Dice \ |	ありす	&	愛梨	&	智絵里	&	薫	&	夕美	&	紗枝	&	柚
     |	0.98	&	0.97	&	0.97	&	0.96	&	0.91	&	0.88	&	0.60
Simpson \ |	柚	&	夕美	&	紗枝	&	薫	&	愛梨	&	智絵里	&	ありす
     |	1.0	&	1.0	&	1.0	&	1.0	&	0.99	&	0.99	&	0.98
Tanimoto \ |	ありす	&	愛梨	&	智絵里	&	薫	&	夕美	&	紗枝	&	柚
     |	0.96	&	0.95	&	0.94	&	0.92	&	0.84	&	0.79	&	0.43
  --------------------------------------------------------------------
  > 順位 (n=4) <|	1	&	2	&	3	&	4	&	5	&	6	&	7
  --------------------------------------------------------------------
 Jaccard \ |	薫	&	愛梨	&	ありす	&	智絵里	&	夕美	&	紗枝	&	柚
      |	0.99	&	0.74	&	0.49	&	0.31	&	0.16	&	0.13	&	0.03
 Dice \ |	薫	&	愛梨	&	ありす	&	智絵里	&	夕美	&	紗枝	&	柚
      |	0.99	&	0.86	&	0.66	&	0.47	&	0.28	&	0.23	&	0.07
 Simpson \ |	柚	&	夕美	&	紗枝	&	薫	&	智絵里	&	ありす	&	愛梨
      |	1.0	&	1.0	&	1.0	&	1.0	&	1.0	&	1.0	&	0.99
 Tanimoto \ |	薫	&	愛梨	&	ありす	&	智絵里	&	夕美	&	紗枝	&	柚
      |	0.99	&	0.75	&	0.49	&	0.31	&	0.16	&	0.13	&	0.03
  --------------------------------------------------------------------
  > 順位 (n=5) <|	1	&	2	&	3	&	4	&	5	&	6	&	7
  --------------------------------------------------------------------
 Jaccard \ |	薫	&	愛梨	&	ありす	&	智絵里	&	夕美	&	紗枝	&	柚
      |	0.76	&	0.14	&	0.11	&	0.05	&	0.03	&	0.01	&	0.00
 Dice \ |	薫	&	愛梨	&	ありす	&	智絵里	&	夕美	&	紗枝	&	柚
      |	0.86	&	0.25	&	0.11	&	0.05	&	0.03	&	0.02	&	0.00
 Simpson \ |	紗枝	&	ありす	&	夕美	&	柚	&	智絵里	&	愛梨	&	薫
      |	0.98	&	0.98	&	0.98	&	0.97	&	0.96	&	0.96	&	0.88
 Tanimoto \ |	薫	&	愛梨	&	ありす	&	智絵里	&	夕美	&	紗枝	&	柚
      |	0.76	&	0.14	&	0.06	&	0.03	&	0.01	&	0.01	&	0.00
//}

n=3までのJaccard,Dice,Tanimotoにおいては、ありすが最も桃華に近い結果になりました。
全体の順位もほとんど変化がありません。
しかし、各類似度の4位くらいまでは類似度が90%以上と非常に高いため、n=3まではどの生物種も類似しているといえます。
n=4からは順位や類似度も変化しました。
なんと薫が最も桃華に似ているという結果になりました。
桃華と薫の類似度はn=5においてもJaccardとTanimotoで76%、Diceで86%と高いです。
アップルパイプリンセスこと愛梨はnが変化しても高い順位 (2位)を保っています。
ですがn=5の場合の類似度においては、JaccardとTanimotoで14%、Diceで25%となり、かなり低くなっています。
Simpsonにおいては、順位が他の類似度と比べて大きく異なっています。
類似度を確認すると、n=5の最下位においても類似度が88%と高いので、あまり順位に意味はないかもしれません。

次に、n-gram (n=2,3,4,5)によるコサイン類似度を計算しました。
以下の@<table>{vector-result}に示します。
集合の時と同様、名前の下には小数点第3位で四捨五入した類似度を示します。

//tabooular[vector-result][ベクトルの類似度]{
  順位 (n=2)	|	1	&	2	&	3	&	4	&	5	&	6	&	7
  ==========>|====&====&====&====&====&====&====
  cos \ |	薫	&	愛梨	&	ありす	&	智絵里	&	柚	&	夕美	&	紗枝
       |	1.0	&	1.0	&	0.99	&	0.98	&	0.96	&	0.96	&	0.95
  --------------------------------------------------------------------
  > 順位 (n=3) <|	1	&	2	&	3	&	4	&	5	&	6	&	7
  --------------------------------------------------------------------
  cos \ |	薫	&	愛梨	&	ありす	&	智絵里	&	夕美	&	紗枝	&	柚
     |	0.99	&	0.96	&	0.96	&	0.90	&	0.87	&	0.79	&	0.72
  --------------------------------------------------------------------
  > 順位 (n=4) <|	1	&	2	&	3	&	4	&	5	&	6	&	7
  --------------------------------------------------------------------
  cos \ |	薫	&	愛梨	&	ありす	&	智絵里	&	夕美	&	紗枝	&	柚
     |	0.97	&	0.72	&	0.72	&	0.51	&	0.47	&	0.34	&	0.25
  --------------------------------------------------------------------
  > 順位 (n=5) <|	1	&	2	&	3	&	4	&	5	&	6	&	7
  --------------------------------------------------------------------
  cos \ |	薫	&	愛梨	&	ありす	&	智絵里	&	夕美	&	紗枝	&	柚
       |	0.80	&	0.31	&	0.30	&	0.17	&	0.16	&	0.13	&	0.09
//}

cosにおいては、nに関係なく順位に大きな変化はありませんでした。
常に類似度1位の薫に注目すると、nが大きくなっても類似度は80%と高い数値でした。
これは集合の場合と同様の結果となります。
つまり薫と桃華は、類似した集合かつベクトルを持っていることがわかります。
次いで高い愛梨やありすに注目してみます。
順位は高いですが、類似度はn=5の場合で両者ともに30%程度と、薫と大きく差が開きました。
しかし、集合の場合と比較すると15~20%程度の類似度の向上が見られました。
これは集合の要素だけではなく、出現回数を考慮しているためと考えられます。

各類似度を調べた結果、ありすより薫のほうが桃華に近かったとわかりました。
花同士なので類似しているのは直感的だと思います。
さらに、安定して愛梨が高い順位を保っていました。
桃華に近いということは、立派なママになる可能性や素質が非常に高いと考えられます。
愛梨ママはなんとなくわかりますが、薫ママは新たな可能性ですね。
当初の目的であるありすと桃華の類似度も、それなりの結果でした。
智絵里 （クローバー）や紗枝 （さくら）よりも桃華 （バラ）に近いのは意外な結果でした。
やはり「思っている以上にいちごはバラに近い」という感じでしょうか。

== おわりに
今回は数種類の花や果物のタンパク質配列を使用して、バラとの類似度を計算してみました。
結果としてバラとひまわり （桃華と薫）は、n=5までのn-gramにおいては類似した集合・ベクトルを持つことがわかりました。
しかし、タンパク質配列の数が生物種によって大きく異なるので、今後データが充実していくと異なる順位になるかもしれません。
データ数の問題は、ウェットな実験屋さんが頑張ってくれるのを待つしかありません。
さらに今回はタンパク質のアミノ酸残基の化学的な意味を考慮していないので、それを考慮した解析を行うと違う結果になると考えられます。

ちなみに私はみりあPです。
みりあを花と例えると、フリージアやルピナス （白）あたりでしょうか。
フリージアの花言葉は「無邪気」や「天真爛漫」などが挙げられます。
ルピナス （白）の花言葉は「いつも幸せ」「母性愛」などです。
つい先日行われたイベント@<fn>{miria}で上位報酬が取れなくて悲しいです。
//footnote[miria][夏祭りDEドリームLIVEフェスティバル]
〇リコンではありません。本当です。
