# 3842. 切换打开灯泡 / Toggle Light Bulbs（简单）
# 核心思路：用长度 101 的状态数组记录每盏灯是否点亮，遍历 bulbs 时对对应位置异或 1 完成切换，最后按编号从小到大收集所有亮着的灯。
# 复杂度：时间 O(n + 100)，空间 O(100)。
class Solution:  # LeetCode 要求的类名
    def toggleLightBulbs(self, bulbs: list[int]) -> list[int]:  # 返回最终处于点亮状态的灯泡编号（升序）
        st = [0] * 101  # st[i] 表示编号 i 的灯泡状态：0 灭、1 亮
        for x in bulbs:  # 依次执行每次切换操作
            st[x] ^= 1  # 异或 1 翻转状态：同一灯泡操作偶数次会恢复熄灭
        return [i for i, x in enumerate(st) if x]  # 按下标升序收集所有亮着的灯泡编号
