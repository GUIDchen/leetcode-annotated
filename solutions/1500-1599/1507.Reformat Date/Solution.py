# 题目：1507. 转变日期格式（Reformat Date）
# 思路：按空白拆分后反转得到「年、月、日」，用月份表把英文月份换成序号，再统一补零拼成 YYYY-MM-DD。
# 时间复杂度：O(L)，L 为日期串长度（常数级）；空间复杂度：O(L)，保存月份表与拆分结果。
class Solution:  # LeetCode 约定的题解类
    def reformatDate(self, date: str) -> str:  # date 形如 "20th Oct 2052"，返回 "2052-10-20"
        s = date.split()  # 按空白切成 ["20th", "Oct", "2052"]
        s.reverse()  # 反转成 ["2052", "Oct", "20th"]，正好对应 年、月、日
        months = " JanFebMarAprMayJunJulAugSepOctNovDec"  # 从下标 1 起每 3 个字符对应一个月份，用于反查月份序号
        s[1] = str(months.index(s[1]) // 3 + 1).zfill(2)  # 定位月份起点除以 3 得 0..11，加 1 后补成两位
        s[2] = s[2][:-2].zfill(2)  # 去掉 "th"/"st"/"nd"/"rd" 后缀，再补成两位
        return "-".join(s)  # 用连字符拼成 YYYY-MM-DD
