# 题目：3170. 删除星号以后字典序最小的字符串（Lexicographically Minimum String After Removing Stars）
# 思路：每个 '*' 删除它左边最小的字母（同字母删最靠右的），用 defaultdict(list) 当 26 个栈保存各字母下标，列表末尾即最靠右位置；标记 rem 后按原顺序拼接剩余字符。
# 时间复杂度：O(n * 26) = O(n)；空间复杂度：O(n)，rem 与各字母下标列表合计保存 n 个位置。
class Solution:  # LeetCode 约定的题解类
    def clearStars(self, s: str) -> str:  # s 只含小写字母与 '*'，返回删除星号后字典序最小的字符串
        g = defaultdict(list)  # g[字母] 是该字母出现过的下标列表，列表末尾（栈顶）就是最靠右的位置
        n = len(s)  # 字符串长度
        rem = [False] * n  # rem[i] 为 True 表示下标 i 的字符要被删除，初始全为 False
        for i, c in enumerate(s):  # 从左到右扫描，i 是下标，c 是字符
            if c == "*":  # 遇到星号
                rem[i] = True  # 星号自身要删除
                for a in ascii_lowercase:  # 按字典序从小到大找第一个还有剩余下标的字母
                    if g[a]:  # 该字母还有没被删掉的出现位置
                        rem[g[a].pop()] = True  # pop 弹出并删除它最靠右的下标，列表末尾即最新位置
                        break  # 每个星号只删一个字符，处理完就跳出内层循环
            else:
                g[c].append(i)  # 否则是普通字母，记录下标，留着以后可能被星号删掉
        return "".join(c for i, c in enumerate(s) if not rem[i])  # 拼接所有未被删除的字符，保持原有顺序
