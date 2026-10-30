# 题目：2678. 老人的数目（Number of Senior Citizens）
# 思路：每位乘客的年龄固定在下标 11、12 这两个字符，切片转成整数后统计严格大于 60 的人数。
# 时间复杂度：O(n)，每个乘客只判断一次；空间复杂度：O(1)，生成器不额外保存列表。
class Solution:  # 统计年龄大于 60 的乘客人数
    def countSeniors(self, details: List[str]) -> int:  # details 是乘客信息字符串列表，返回老人的人数
        return sum(int(x[11:13]) > 60 for x in details)  # 切片取年龄两位并转整数，比较得到的 True/False 交给 sum 累加
