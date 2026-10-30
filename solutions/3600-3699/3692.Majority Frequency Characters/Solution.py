# 3692. Majority Frequency Characters（3692. 众数频率字符）
# 核心思路：先统计每个字母的出现次数，把“出现次数相同的字母”聚成一组；在所有组中取组大小最大者（并列时取出现次数更大的那组），组内字母按字典序拼接返回。
# 复杂度：时间 O(n + 26 log 26)，空间 O(26)，n 为字符串长度。
class Solution:  # 定义题解类
    def majorityFrequencyGroup(self, s: str) -> str:  # 主函数：返回“众数频率组”里的所有字母
        cnt = Counter(s)  # 统计每个字符的出现次数
        f = defaultdict(list)  # 用“出现次数 -> 字母列表”把同频字符聚成一组
        for c, v in cnt.items():  # 遍历每个字符及其出现次数
            f[v].append(c)  # 把字符放进对应频率的组里
        mx = mv = 0  # mx 为最大组大小，mv 为该组的出现频率
        ans = []  # ans 保存最终选中那组的字母列表
        for v, cs in f.items():  # 遍历每个频率分组
            if mx < len(cs) or (mx == len(cs) and mv < v):  # 组更大则更新；组大小相同则取频率更大者
                mx = len(cs)  # 更新最大组大小
                mv = v  # 更新对应的出现频率
                ans = cs  # 记录该组的字母列表
        return "".join(ans)  # 拼接成字符串返回
