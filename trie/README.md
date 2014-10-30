trie
==============

# [Trie@Wikipedia](http://zh.wikipedia.org/wiki/Trie)

这里有1个Trie(字典树)的例子，使用场景是查询联系人名称的首字母全拼，比如字典中若存在‘汪伯宽’和‘汪仲渊’，搜索‘w'时应返回这2条记录。

* 每个节点有26个子节点，1个父节点的2级指针
* 每次搜索时会在Trie中暂存临时状态，使用2级指针方便快速计算某节点的排行而不用多开辟存储单元

# 编译

`git clone https://github.com/hubugui/ds.git`

`cd ds/trie`

`make`

# 运行

最后1个参数是要搜索的字符串，其余参数是全拼字母，如：

`./trie wy wbk wzy w`

返回

`total string count=3`

`total node count=6`


`searching 'w':`

`01:'wbk', len=3`

`02:'wy', len=2`

`03:'wzy', len=3`

`3 results`

*其他例子*

`./trie wy wbk wbkk wzg s sshc sgf sgfb sgfbk sgfk syb szhf sy`
