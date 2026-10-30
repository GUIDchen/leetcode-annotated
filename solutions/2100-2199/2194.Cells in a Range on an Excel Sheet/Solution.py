# 题目：2194. Excel 表中某个范围内的单元格（Cells in a Range on an Excel Sheet）
# 思路：把区间串的两个端点解析成列字母与行号，用嵌套推导式按“先列后行”生成全部单元格名。
# 时间复杂度：O(rows·cols)，与输出规模同阶；空间复杂度：O(rows·cols)，存放结果。
class Solution:  # LeetCode 约定的题解类
    def cellsInRange(self, s: str) -> List[str]:  # s 形如 K1:L2，s[0]/s[1] 是起点列与行，s[-2]/s[-1] 是终点列与行
        return [  # 列表推导式，先列后行地生成区间内的所有单元格
            chr(i) + str(j)  # chr 把列序号还原成字母，再拼上行号
            for i in range(ord(s[0]), ord(s[-2]) + 1)  # 列从起始字母枚举到结束字母
            for j in range(int(s[1]), int(s[-1]) + 1)  # 行从起始行号枚举到结束行号
        ]  # 推导式到此结束
