# 题目：2456. 最流行的视频创作者（Most Popular Video Creator）
# 思路：哈希表 cnt 统计每位创作者的总播放量，哈希表 d 记录其播放量最高（并列取 id 字典序最小）的视频下标；
# 求出最大总播放量后，用列表推导收集并列最高者的「作者名 + 最佳视频 id」。
# 时间复杂度：O(n)，遍历数组一次加若干次哈希表操作；空间复杂度：O(n)，两个哈希表存每位创作者的信息。
class Solution:  # LeetCode 约定的题解类
    # 返回总播放量最高的创作者列表，每项为 [作者名, 其播放量最高的视频 id]（并列最高时全部返回）
    def mostPopularCreator(
        # 三个平行列表：creators 作者名、ids 视频 id、views 播放量
        self, creators: List[str], ids: List[str], views: List[int]
    ) -> List[List[str]]:
        cnt = defaultdict(int)  # 作者 → 总播放量，缺省值为 0，可直接做 +=
        d = defaultdict(int)  # 作者 → 播放量最高（并列时 id 字典序最小）的视频下标
        for k, (c, i, v) in enumerate(zip(creators, ids, views)):  # 三表同步遍历，k 是下标，c/i/v 分别是作者、id、播放量
            cnt[c] += v  # 该作者的总播放量累加上当前视频的播放量
            if c not in d or views[d[c]] < v or (views[d[c]] == v and ids[d[c]] > i):  # 该作者还没记录，或播放量更高，或播放量相同但 id 字典序更小
                d[c] = k  # 更新该作者的最佳视频下标为当前视频
        mx = max(cnt.values())  # 所有创作者中的最大总播放量
        return [[c, ids[d[c]]] for c, x in cnt.items() if x == mx]  # 收集总播放量等于最大值的作者及其最佳视频 id
