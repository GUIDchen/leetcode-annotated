// 3661. Maximum Walls Destroyed by Robots（3661. 可以被机器人摧毁的最大墙壁数目）
// 核心思路：机器人按位置排序后，从左至右做记忆化搜索，f[i][j] 表示处理前 i+1 个机器人、右邻居是否已向左射击时的最大摧毁数；每个机器人选朝左或朝右打，用二分统计区间内的墙壁数。
// 复杂度：时间 O(n log m + n log n)，空间 O(n)，其中 m 为墙壁数量。
class Solution {  // 定义题解类
public:  // 公有成员，供判题器调用
    int maxWalls(vector<int>& robots, vector<int>& distance, vector<int>& walls) {  // 求所有机器人最多能摧毁的墙壁数目
        int n = robots.size();  // 机器人数量
        vector<pair<int, int>> arr(n);  // 把每个机器人的位置与射程打包成 (位置, 射程)
        for (int i = 0; i < n; i++) {  // 逐个打包
            arr[i] = {robots[i], distance[i]};  // 记录第 i 个机器人的位置与射程
        }  // 结束打包循环
        ranges::sort(arr, {}, &pair<int, int>::first);  // 按机器人位置升序排序
        ranges::sort(walls);  // 墙壁坐标升序排序，便于用二分统计区间

        vector f(n, vector<int>(2, -1));  // 记忆化表：f[i][j] 表示处理到第 i 个机器人、右侧邻居状态为 j 时的最大摧毁数

        auto dfs = [&](this auto&& dfs, int i, int j) -> int {  // 定义记忆化搜索：j=0 表示右邻居 i+1 已向左射击，j=1 表示它没有占左侧区间
            if (i < 0) {  // 没有机器人可处理
                return 0;  // 贡献为 0
            }  // 结束边界判断
            if (f[i][j] != -1) {  // 该状态已经计算过
                return f[i][j];  // 直接返回缓存结果
            }  // 结束缓存判断

            int left = arr[i].first - arr[i].second;  // 向左能打到的最远位置
            if (i > 0) {  // 不是最左边的机器人，需要与左邻居划分边界
                left = max(left, arr[i - 1].first + 1);  // 不能越过左侧机器人的位置，避免重复计数
            }  // 结束左边界修正
            int l = ranges::lower_bound(walls, left) - walls.begin();  // 左区间起点在墙壁数组中的下标
            int r = ranges::lower_bound(walls, arr[i].first + 1) - walls.begin();  // 左区间终点（不含机器人自身位置）在墙壁数组中的下标
            int ans = dfs(i - 1, 0) + (r - l);  // 选择向左打：统计区间内墙壁数，并递归处理左边且告知右邻居已向左射击

            int right = arr[i].first + arr[i].second;  // 向右能打到的最远位置
            if (i + 1 < n) {  // 右侧还有机器人，需要协商边界
                if (j == 0) {  // 右邻居 i+1 已经向左射击
                    right = min(right, arr[i + 1].first - arr[i + 1].second - 1);  // 边界卡在它向左射程之外，避免重复计数
                } else {  // 否则右邻居没有占用左侧区间
                    right = min(right, arr[i + 1].first - 1);  // 边界卡在它自身位置之前
                }  // 结束右边界协商
            }  // 结束右侧机器人判断
            l = ranges::lower_bound(walls, arr[i].first) - walls.begin();  // 右区间起点（从机器人自身位置开始）在墙壁数组中的下标
            r = ranges::lower_bound(walls, right + 1) - walls.begin();  // 右区间终点在墙壁数组中的下标
            ans = max(ans, dfs(i - 1, 1) + (r - l));  // 选择向右打：取向左打与向右打两种方案的较大值

            return f[i][j] = ans;  // 记忆化并返回当前状态的最优解
        };  // 结束搜索函数定义

        return dfs(n - 1, 1);  // 从最右边的机器人开始，其右侧没有机器人与之争抢
    }  // 结束方法
};  // 结束题解类
