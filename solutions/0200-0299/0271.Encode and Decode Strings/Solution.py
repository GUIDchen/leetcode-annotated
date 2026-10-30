# 题目：271. 字符串的编码与解码（Encode and Decode Strings）
# 思路：每个字符串前拼上固定 4 位宽度的长度前缀（右对齐补空格），解码时先读 4 个字符得到长度，再按长度切出正文。
# 时间复杂度：O(n)，n 为所有字符总数，编码/解码各扫描一遍；空间复杂度：O(n)，编码串与结果列表都存放全部内容。
class Codec:  # 编解码器类：encode 打包成单个字符串，decode 再还原成列表
    def encode(self, strs: List[str]) -> str:  # strs：待编码的字符串列表
        """Encodes a list of strings to a single string."""  # 文档字符串：说明本方法把列表编码成单个字符串
        ans = []  # 收集每一段「长度前缀 + 正文」
        for s in strs:  # 逐个处理字符串
            ans.append("{:4}".format(len(s)) + s)  # 长度右对齐占 4 个字符，再拼上原字符串
        return "".join(ans)  # 拼接成一个完整的编码串

    def decode(self, s: str) -> List[str]:  # s：encode 生成的编码串
        """Decodes a single string to a list of strings."""  # 文档字符串：说明本方法把编码串还原成列表
        ans = []  # 保存解码出的字符串
        i, n = 0, len(s)  # i：当前读取位置；n：编码串长度
        while i < n:  # 只要没读完就继续解析下一段
            size = int(s[i : i + 4])  # 读出 4 位长度前缀并转成整数
            i += 4  # 跳过长度前缀
            ans.append(s[i : i + size])  # 按长度切出正文，放入结果
            i += size  # 跳过正文，准备下一段的起点
        return ans  # 返回解码后的字符串列表


# Your Codec object will be instantiated and called as such:
# codec = Codec()
# codec.decode(codec.encode(strs))
