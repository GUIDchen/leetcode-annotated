# 3846. 使用单指输入字符串的总距离 / Total Distance to Type a String Using One Finger（中等）
# 核心思路：预先建好 QWERTY 键盘的字母坐标表，再按序累加手指从上一键到下一键的曼哈顿距离。
# 复杂度：时间 O(|s|)，空间 O(1)。
pos = {}  # 全局字典：字母到键盘坐标 (行, 列) 的映射
keys = ['qwertyuiop', 'asdfghjkl', 'zxcvbnm']  # 键盘三行布局
for i, row in enumerate(keys):  # 逐行遍历
    for j, key in enumerate(row):  # 逐列遍历
        pos[key] = (i, j)  # 记录该字母的行列坐标


class Solution:  # 题解类（LeetCode 约定类名）
    def totalDistance(self, s: str) -> int:  # 返回从起始键 'a' 出发、按顺序敲出 s 的总移动距离
        pre = 'a'  # 手指当前位置，初始在 'a'
        ans = 0  # 累计移动距离
        for cur in s:  # 依次敲击每个字符
            x1, y1 = pos[pre]  # 当前手指所在键的坐标
            x2, y2 = pos[cur]  # 目标键的坐标
            dist = abs(x1 - x2) + abs(y1 - y2)  # 两键之间的曼哈顿距离
            ans += dist  # 累加到总距离
            pre = cur  # 手指移动到目标键，成为下一次的起点
        return ans  # 返回总移动距离
