# 题目：1585. 检查字符串是否可以通过排序子字符串得到另一个字符串（Check If String Is Transformable With Substring Sort Operations）
# 思路：排序子串只会让较小的数字往左移，因此按 t 逐位消费数字时，若有更小的数字还挡在它前面，就永远无法完成。
# 时间复杂度：O(n * 10)，每个字符最多检查 10 个更小的数字；空间复杂度：O(n)，保存各数字的下标队列。
class Solution:  # LeetCode 约定的题解类
    def isTransformable(self, s: str, t: str) -> bool:  # s 为原串，t 为目标串
        pos = defaultdict(deque)  # pos[d] 保存数字 d 在 s 中的下标队列（按先后顺序）
        for i, c in enumerate(s):  # 扫描 s，记录每个数字出现的位置
            pos[int(c)].append(i)  # 字符转整数后按顺序入队
        for c in t:  # 按目标串的顺序逐个消费数字
            x = int(c)  # 当前需要的数字
            if not pos[x] or any(pos[i] and pos[i][0] < pos[x][0] for i in range(x)):  # x 已用尽，或有更小的数字挡在 x 前面
                return False  # 这两种情况都无法靠排序子串达成
            pos[x].popleft()  # x 就位，弹出它最靠前的那个位置
        return True  # 全部消费完即说明可以变换
