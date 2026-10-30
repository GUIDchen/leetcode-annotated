// 题目：2462. 雇佣 K 位工人的总代价（Total Cost to Hire K Workers）
// 思路：维护左右两端各 candidates 人的小根堆，每轮弹出代价最小者并从同一侧补入下一个候选；两侧区间重叠时直接排序取前 k 小。
// 时间复杂度：O((n + k) log candidates)，堆大小不超过 2*candidates；空间复杂度：O(candidates)。
class Solution {  // LeetCode 题解类
public:  // 判题器通过 public 区调用下面的方法
    long long totalCost(vector<int>& costs, int k, int candidates) {  // costs 是每个工人的代价，k 是雇佣人数，candidates 是每次可选的两侧候选人数
        int n = costs.size();  // 工人总数
        if (candidates * 2 > n) {  // 特判：两侧候选区间会重叠甚至覆盖全部工人，此时每轮都能直接挑全局最小值
            sort(costs.begin(), costs.end());  // 升序排序，最小值都排在前面
            return accumulate(costs.begin(), costs.begin() + k, 0LL);  // 取最小的 k 个代价求和即为答案；0LL 保证 accumulate 以 long long 累加
        }  // 特判分支结束
        using pii = pair<int, int>;  // 别名：配对（代价, 下标），小根堆会先比 first 再比 second
        priority_queue<pii, vector<pii>, greater<pii>> pq;  // 小根堆，保存当前左右两端候选人的（代价, 下标）；greater 使其成为最小堆
        for (int i = 0; i < candidates; ++i) {  // 把左右两端各 candidates 个人放进堆
            pq.emplace(costs[i], i);  // 左端第 i 个人入堆
            pq.emplace(costs[n - i - 1], n - i - 1);  // 右端倒数第 i+1 个人入堆，下标 n-i-1 用于后面判断该从哪侧补人
        }  // 初始候选集合构造完毕
        long long ans = 0;  // 累计总代价，最坏可达 10^11 量级，必须用 long long
        int l = candidates, r = n - candidates - 1;  // l 是左端下一个待补入的下标，r 是右端下一个待补入的下标
        while (k--) {  // 循环 k 轮：k 每轮自减，减到 0 时条件为假、循环结束
            auto [cost, i] = pq.top();  // 取出小根堆堆顶，cost 为代价、i 为原始下标（结构化绑定）
            pq.pop();  // 弹出堆顶，表示该工人被雇佣
            ans += cost;  // 把这份代价累加进总代价
            if (l > r) {  // l > r 表示左右候选区间已经相遇，没有新候选可补
                continue;  // 跳过补水逻辑，直接进入下一轮
            }  // 补人逻辑的前提判断结束
            if (i < l) {  // 被雇佣者来自左端，就从左端补一个新候选进堆
                pq.emplace(costs[l], l++);  // 放入 costs[l] 并把左指针右移一格（后缀自增先取值再加一）
            } else {  // 否则被雇佣者来自右端
                pq.emplace(costs[r], r--);  // 放入 costs[r] 并把右指针左移一格
            }  // 补人结束
        }  // 已雇佣满 k 人，循环退出
        return ans;  // 返回最小总代价
    }  // 方法结束
};  // 类定义结束（源文件末尾没有换行，保持原样）