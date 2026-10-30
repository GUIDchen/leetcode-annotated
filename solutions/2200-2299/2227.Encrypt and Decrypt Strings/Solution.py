# 题目：2227. 加密解密字符串（Encrypt and Decrypt Strings）
# 思路：加密用「明文字符 → 密文」字典；解密不回溯，而是在构造时把字典词全部加密并统计密文出现次数，解密时直接查表。
# 时间复杂度：构造 O(D·L)，encrypt O(L)，decrypt O(1)；空间复杂度：O(D·L)，D 为字典词数、L 为单词长度。
class Encrypter:  # 题目要求的加密器类
    def __init__(self, keys: List[str], values: List[str], dictionary: List[str]):  # 构造函数：keys/values 给出加密表，dictionary 用来预统计密文词频
        self.mp = dict(zip(keys, values))  # 用 zip 把两个列表压成 明文字符 → 密文 的字典
        self.cnt = Counter(self.encrypt(v) for v in dictionary)  # 把每个字典词的密文作为键计数，解密时只需查表

    def encrypt(self, word1: str) -> str:  # 加密：逐字符替换为对应密文，缺映射时返回空串
        res = []  # 用列表累积密文片段，最后一次性拼接
        for c in word1:  # 遍历明文的每个字符
            if c not in self.mp:  # 该字符没有对应的密文
                return ''  # 按题意返回空串表示无法加密
            res.append(self.mp[c])  # 追加该字符的密文
        return ''.join(res)  # 拼接成完整密文返回

    def decrypt(self, word2: str) -> int:  # 解密：返回能加密成该密文的字典单词个数
        return self.cnt[word2]  # 直接查词频表，没出现过则计 0


# 下面是 LeetCode 判题器给出的调用示例，不是题解代码
# Your Encrypter object will be instantiated and called as such:
# obj = Encrypter(keys, values, dictionary)
# param_1 = obj.encrypt(word1)
# param_2 = obj.decrypt(word2)
