// 题目：857. 雇佣 K 名工人的最低成本（Minimum Cost to Hire K Workers）
// 思路：按「工资/质量」比值升序排序，枚举每个人的比值作为全员统一单价，同时用大根堆维护质量总和最小的 k 人。
// 时间复杂度：O(n log n)，排序与堆操作；空间复杂度：O(n)，比值数组与堆。
class Solution {  // 题解类
public:
    double mincostToHireWorkers(vector<int>& quality, vector<int>& wage, int k) {  // quality 为每人的工作质量，wage 为最低期望工资，k 为要雇佣的人数
        int n = quality.size();  // 工人数量
        vector<pair<double, int>> t(n);  // 存 (工资/质量 的比值, 质量)，按比值排序
        for (int i = 0; i < n; ++i) {  // 逐个工人计算比值
            t[i] = {(double) wage[i] / quality[i], quality[i]};  // 比值决定统一单价，质量决定在该单价下的实际花销
        }  // 比值计算完毕
        sort(t.begin(), t.end());  // 按比值升序排序，保证枚举到当前人时他的比值是所选 k 人中的最大值
        priority_queue<int> pq;  // 大根堆存已选工人的质量，便于淘汰质量最大者
        double ans = 1e18;  // 答案先初始化为一个足够大的数
        int tot = 0;  // 当前选中工人的质量总和
        for (auto& [x, q] : t) {  // 以当前比值 x 作为统一单价
            tot += q;  // 把当前工人的质量加入总和
            pq.push(q);  // 同时入堆
            if (pq.size() == k) {  // 已凑够 k 人，可以结算一次成本
                ans = min(ans, tot * x);  // 成本 = 质量总和 × 统一单价
                tot -= pq.top();  // 为后续枚举做准备：先把质量最大者的质量从总和中减掉
                pq.pop();  // 再从堆中真正删除
            }  // 结算分支结束
        }  // 枚举结束
        return ans;  // 返回最小总成本
    }  // 方法结束
};  // 题解类结束