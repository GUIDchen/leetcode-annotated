# 题目：1762. 能看到海景的建筑物（Buildings With an Ocean View）🔒
# 思路：从右往左扫描并维护右侧最高高度，当前建筑严格更高才看得到海；最后把下标反转成升序。
# 时间复杂度：O(n)，一次扫描加一次反转；空间复杂度：O(n)，存放答案下标。
class Solution:  # LeetCode 约定的题解类
    def findBuildings(self, heights: List[int]) -> List[int]:  # heights：从左到右的建筑高度
        ans = []  # 收集能看到海景的建筑下标，按从右往左的顺序
        mx = 0  # 当前已扫描到的右侧最高高度，海平面视为 0
        for i in range(len(heights) - 1, -1, -1):  # 从最右侧开始向左倒序遍历
            if heights[i] > mx:  # 严格高于右侧所有建筑，视线不被遮挡
                ans.append(i)  # 记录该建筑下标
                mx = heights[i]  # 更新右侧最高高度
        return ans[::-1]  # 用步长 -1 的切片反转，得到从左到右的下标顺序
