# 题目：535. TinyURL 的加密与解密（Encode and Decode TinyURL）
# 思路：自增计数当短码，用哈希表建立「短码 → 原链接」的映射；解密时按 '/' 切出最后一段短码再查表。
# 时间复杂度：encode / decode 均 O(L)，L 是链接长度；空间复杂度：O(n*L)，保存所有历史链接。
class Codec:  # LeetCode 约定的编解码类（本题类名是 Codec 而不是 Solution）
    def __init__(self):  # 构造函数：初始化映射表、计数器和域名
        self.m = defaultdict()  # 短码 → 原链接 的映射表
        self.idx = 0  # 自增计数器，保证每次编码出来的短码都不重复
        self.domain = 'https://tinyurl.com/'  # 短链接的固定域名前缀

    def encode(self, longUrl: str) -> str:  # 编码：把长链接变成短链接
        """Encodes a URL to a shortened URL."""  # 题目给定的接口说明文档字符串
        self.idx += 1  # 计数器自增，得到一个新的唯一编号
        self.m[str(self.idx)] = longUrl  # 以编号的字符串形式为键，把原链接存进映射表
        return f'{self.domain}{self.idx}'  # 域名加编号拼成短链接返回

    def decode(self, shortUrl: str) -> str:  # 解码：把短链接还原成长链接
        """Decodes a shortened URL to its original URL."""  # 题目给定的接口说明文档字符串
        idx = shortUrl.split('/')[-1]  # 按 '/' 切分后取最后一段，就是当初生成的短码
        return self.m[idx]  # 用短码查表，取出原始长链接


# Your Codec object will be instantiated and called as such:
# codec = Codec()
# codec.decode(codec.encode(url))
