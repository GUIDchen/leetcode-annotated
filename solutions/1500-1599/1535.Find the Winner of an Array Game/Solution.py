# 题目：1535. 找出数组游戏的赢家（Find the Winner of an Array Game）
# 思路：mx 维护当前擂主（同样也是已扫描部分的最大值），cnt 记录其连胜场次，达到 k 就停；扫描完仍不够 k 场时最大值必胜。
# 时间复杂度：O(n)，一趟扫描；空间复杂度：O(1)，只维护几个变量。
class Solution:  # LeetCode 约定的题解类
    def getWinner(self, arr: List[int], k: int) -> int:  # arr 是参赛数组，k 是夺冠所需的连续获胜次数
        mx = arr[0]  # 擂主初始为第一个元素
        cnt = 0  # 连胜计数器从 0 开始
        for x in arr[1:]:  # 从第二个元素开始逐个挑战擂主
            if mx < x:  # 挑战者更大，擂主换人
                mx = x  # 把擂主更新为这个更大的元素
                cnt = 1  # 新擂主刚赢一场，连胜数重置为 1
            else:  # 否则擂主更大，继续守擂
                cnt += 1  # 守擂成功，连胜次数加一
            if cnt == k:  # 连胜达到 k 场，赢家已定
                break  # 提前结束循环
        return mx  # 返回赢家；没到 k 场时最大值也会在后续持续获胜
