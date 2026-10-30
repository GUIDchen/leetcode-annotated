# 3913. Sort Vowels by Frequency | 按频率对元音排序（中等）
# 核心思路：先统计每个元音字母出现的次数，再按频次降序给出现过的元音字母排序；然后把排序后的字母依次填回原串中那些“元音位置”（非元音位置保持不动），每填写一个就把对应频次减一，配额用完就换下一个字母。
# 复杂度：时间 O(n + V log V)，V 至多为 5（元音种类数）；空间 O(n + V)，用于结果串与频次表。
class Solution:  # 定义题解类
    def sortVowels(self, s: str) -> str:  # 把元音字母按出现频率降序重排，非元音字符保持原位
        st = set("aeiou")  # 元音字符集合（题目只考虑小写）
        vowels = []  # 出现过的元音字母，每个字母只存一份
        cnt = Counter()  # 每个元音字母的剩余出现次数
        for c in s:  # 第一遍扫描：统计元音频次
            if c not in st:  # 当前字符不是元音
                continue  # 跳过，保持原位
            if c not in cnt:  # 第一次遇到这个元音字母
                vowels.append(c)  # 记录该元音字母（相同字母只记一次）
            cnt[c] += 1  # 该元音的频次加一
        vowels.sort(key=lambda c: -cnt[c])  # 按频次降序排列这些元音字母（用负号把降序转成升序键）
        ans = list(s)  # 转成列表作为答案的基底，非元音位置直接沿用
        i = 0  # 指向当前正在填写的元音字母
        for k, c in enumerate(s):  # 第二遍扫描：把排好序的元音依次写回元音位置
            if c not in st:  # 原串当前位置不是元音
                continue  # 跳过，该位置内容不变
            ans[k] = c = vowels[i]  # 取出当前应填的元音并写入该位置（链式赋值同时把这个字母记到 c 上）
            cnt[c] -= 1  # 该字母的剩余配额减一
            if cnt[c] == 0:  # 配额减到 0 说明用完了
                i += 1  # 换到下一个元音字母
        return "".join(ans)  # 拼回字符串返回
