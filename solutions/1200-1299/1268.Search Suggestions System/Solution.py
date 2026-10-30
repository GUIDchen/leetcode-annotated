class Trie:  # 字典树节点：children 是 26 个孩子，v 存该前缀下最多 3 个产品下标
    def __init__(self):  # 构造函数：初始化孩子数组与候选列表
        self.children: List[Union[Trie, None]] = [None] * 26  # 26 个小写字母对应的孩子位置，初始都为空
        self.v: List[int] = []  # 当前前缀下按字典序排好的产品下标，最多 3 个

    def insert(self, w, i):  # 把第 i 个单词 w 逐字符插入字典树
        node = self  # 从根节点开始向下遍历
        for c in w:  # 沿着 w 的每个字符向下，覆盖它的所有前缀
            idx = ord(c) - ord('a')  # 字符映射到 0..25 的下标
            if node.children[idx] is None:  # 该字符对应的子节点还没建出来
                node.children[idx] = Trie()  # 新建子节点，把这条前缀路径补全
            node = node.children[idx]  # 下移到该前缀节点
            if len(node.v) < 3:  # 每个前缀最多只保留 3 个推荐
                node.v.append(i)  # 记录产品下标；products 已排序，下标升序即字典序

    def search(self, w):  # 返回 searchWord 每个前缀对应的产品下标列表
        node = self  # 从根节点开始匹配前缀
        ans = [[] for _ in range(len(w))]  # 答案按前缀个数预分配，没匹配到的前缀保持空列表
        for i, c in enumerate(w):  # 逐字符拼出 searchWord 的每一个前缀
            idx = ord(c) - ord('a')  # 字符映射到 0..25 的下标
            if node.children[idx] is None:  # 字典树里已经不存在这个前缀
                break  # 更长的前缀必然也不存在，直接跳出循环
            node = node.children[idx]  # 下移到当前前缀节点
            ans[i] = node.v  # 取出该前缀的候选下标
        return ans  # 返回每个前缀的推荐结果


class Solution:  # LeetCode 约定的题解类
    def suggestedProducts(  # products：待搜索商品列表；searchWord：用户逐字输入的搜索词
        self, products: List[str], searchWord: str  # 参数续行：两个输入参数的类型标注
    ) -> List[List[str]]:  # 返回值是每个前缀对应的一串推荐商品
        products.sort()  # 先排序，保证每个前缀取到的都是字典序最小的 3 个
        trie = Trie()  # 建立字典树
        for i, w in enumerate(products):  # 枚举商品及其下标
            trie.insert(w, i)  # 把单词插入字典树并记录下标
        return [[products[i] for i in v] for v in trie.search(searchWord)]  # 下标翻译回商品名，组成每个前缀的推荐结果
