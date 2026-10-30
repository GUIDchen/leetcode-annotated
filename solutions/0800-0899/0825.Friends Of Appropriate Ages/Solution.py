# 题目：825. 适龄的朋友（Friends Of Appropriate Ages）
# 思路：年龄只有 1..120 共 120 种取值，先统计每种年龄的人数，再枚举「发送者年龄 ax、接收者年龄 ay」的所有组合，剔除题目给出的三种不发送情况后按人数相乘累加。
# 时间复杂度：O(m^2 + n)，m = 121 为年龄上限，n 为人数；空间复杂度：O(m)，计数数组大小固定。
class Solution:  # LeetCode 约定的题解类
    def numFriendRequests(self, ages: List[int]) -> int:  # ages 是所有人的年龄，返回合法好友请求的对数
        cnt = [0] * 121  # 长度 121 的计数数组，cnt[x] 表示年龄为 x 的人数
        for x in ages:  # 遍历每个年龄，做桶计数
            cnt[x] += 1  # 对应年龄的人数加一
        ans = 0  # 答案累加器
        for ax, x in enumerate(cnt):  # enumerate 同时给出年龄 ax 与对应人数 x，一次循环就能枚举发送者年龄
            for ay, y in enumerate(cnt):  # 同样地枚举接收者年龄 ay 与人数 y
                if not (ay <= 0.5 * ax + 7 or ay > ax or (ay > 100 and ax < 100)):  # 三个「不发送」条件：ay 太年轻、ay 比 ax 大、ay 超 100 而 ax 不到 100；not 之后才是可发送
                    ans += x * (y - int(ax == ay))  # 可发送的组合数为 x * y；同年龄时要去掉自己加自己，故用 int(ax == ay) 减去 1
        return ans  # 返回合法请求总数
