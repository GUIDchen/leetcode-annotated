// 3534. 针对图的路径存在性查询 II / Path Existence Queries in a Graph II
// 核心思路：按数值排序后滑动窗口求出每个点一步能到的最远点，再用二进制倍增表 f[i][k] 从高位到低位贪心逼近，累加最少步数。
// 复杂度：时间 O(n log n + (n + q) log n)，空间 O(n log n)。
class Solution {  // 定义题解类
public:  // 公有方法区
    vector<int> pathExistenceQueries(int n, vector<int>& nums, int maxDiff, vector<vector<int>>& queries) {  // 回答：从 i 到 j 的最少步数，不可达返回 -1
        vector<pair<int, int>> pairs;  // 按数值升序保存 (数值, 原始下标)
        for (int i = 0; i < n; i++) {  // 收集所有元素
            pairs.emplace_back(nums[i], i);  // 记录数值与原始下标
        }  // 循环结束
        sort(pairs.begin(), pairs.end());  // 按数值升序排序，便于用双指针找一步可达的最远点

        int m = 20;  // 倍增表层数，2^20 已大于元素个数上限
        vector<vector<int>> f(n, vector<int>(m));  // f[i][k]：从 i 跳 2^k 步后能到达的下标
        int r = n - 1;  // 滑动窗口右端，初始在最右侧
        for (int l = n - 1; l >= 0; l--) {  // 左端从右往左移动
            while (pairs[r].first - pairs[l].first > maxDiff) {  // 窗口两端差超过 maxDiff 时收缩右端，直到可直接连边
                r--;  // 收缩窗口右端
            }  // while 循环结束
            int i = pairs[l].second, j = pairs[r].second;  // 换算回原始下标 i 与最远可达下标 j
            f[i][0] = j;  // 跳 1 步能到的最远点
            for (int k = 1; k < m; k++) {  // 逐层构造倍增表
                f[i][k] = f[f[i][k - 1]][k - 1];  // 2^k 步 = 先跳 2^(k-1) 步，再跳 2^(k-1) 步
            }  // 内层循环结束
        }  // 外层循环结束

        vector<int> ans;  // 存放每个查询的答案
        for (auto& q : queries) {  // 逐个处理查询
            int i = q[0], j = q[1];  // 取出查询的两个端点
            if (nums[i] > nums[j]) {  // 保证起点数值不大于终点数值，便于统一处理
                swap(i, j);  // 交换两端
            }  // if 语句结束
            if (i == j) {  // 起点与终点是同一个下标
                ans.push_back(0);  // 无需移动，步数为 0
                continue;  // 处理下一个查询
            }  // if 语句结束
            if (nums[i] == nums[j]) {  // 数值相同但下标不同，说明二者在同一个可连边组内
                ans.push_back(1);  // 只需 1 步
                continue;  // 处理下一个查询
            }  // if 语句结束
            int d = 0;  // d：已累计跳过的步数
            for (int k = m - 1; k >= 0; k--) {  // 从高位到低位尝试跳跃，贪心逼近 j
                if (nums[f[i][k]] < nums[j]) {  // 跳 2^k 步后仍未达到 j 的数值
                    d |= 1 << k;  // 把这 2^k 步计入累计步数
                    i = f[i][k];  // 真正移动过去
                }  // if 语句结束
            }  // 循环结束
            if (nums[f[i][0]] < nums[j]) {  // 再走一步仍到不了 j，说明不可达
                ans.push_back(-1);  // 记为 -1
            } else {  // 否则再走一步即可到达
                ans.push_back(d + 1);  // 总步数 = 已跳步数 + 1
            }  // if 语句结束
        }  // 循环结束
        return ans;  // 返回全部查询的答案
    }  // 方法结束
};  // 类定义结束