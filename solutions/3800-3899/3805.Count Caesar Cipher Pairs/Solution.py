# 题目：3805. 统计凯撒加密对数目（Count Caesar Cipher Pairs）
# 思路：把每个单词循环平移成「首字母为 z」的规范形式，规范形式相同的单词两两互为凯撒加密，按组合数累加。
# 时间复杂度：O(L)，L 为所有单词的总字符数；空间复杂度：O(L)，哈希表按规范形式统计个数。
class Solution:  # LeetCode 约定的题解类
    def countPairs(self, words: List[str]) -> int:  # 统计可以通过凯撒整体平移互相转化的单词对数量
        cnt = defaultdict(int)  # 键：归一化后的字符串；值：该归一化形式出现的次数
        for s in words:  # 遍历每个单词
            t = list(s)  # 转成字符列表，便于按下标修改
            k = ord("z") - ord(t[0])  # 让首字母平移到 'z' 所需的位移量
            for i in range(1, len(t)):  # 对首字母之后的每个字符做同样的平移
                t[i] = chr((ord(t[i]) - ord("a") + k) % 26 + ord("a"))  # 在字母表上循环右移 k 位
            t[0] = "z"  # 首字母统一设为 'z'，使平移后的单词也能直接比较
            cnt["".join(t)] += 1  # 归一化形式相同的单词归为一类
        return sum(v * (v - 1) // 2 for v in cnt.values())  # 同类内任意两个都能互相转化，累加组合数 C(v,2)
