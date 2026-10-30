// 题目：1383. 最大的团队表现值（Maximum Performance of a Team）
// 思路：按效率降序枚举「团队效率下限」，用小根堆维护速度最大的 k 人，用速度之和乘当前效率更新答案。
// 时间复杂度：O(n log n)，排序与堆操作；空间复杂度：O(n)，存打捆后的数组与堆。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maxPerformance(int n, vector<int>& speed, vector<int>& efficiency, int k) {  // n 人数，k 团队上限
        vector<pair<int, int>> t(n);  // 把 (效率, 速度) 打捆，效率取负便于直接升序排序
        for (int i = 0; i < n; ++i) t[i] = {-efficiency[i], speed[i]};  // 负效率做第一关键字，等价于效率降序
        sort(t.begin(), t.end());  // 按效率从高到低处理每个工程师
        priority_queue<int, vector<int>, greater<int>> q;  // 小根堆：随时能弹出当前团队里速度最小的人
        long long ans = 0, tot = 0;  // ans 记录最优表现值，tot 是当前团队的速度之和
        int mod = 1e9 + 7;  // 题目要求的取模常量
        for (auto& x : t) {  // 依次把当前工程师的效率当作团队效率下限
            int s = x.second, e = -x.first;  // 还原速度 s 和效率 e
            tot += s;  // 先把当前工程师加入团队
            ans = max(ans, tot * e);  // 表现值 = 速度和 × 当前效率下限，用它更新答案
            q.push(s);  // 速度入堆，方便之后淘汰最慢的人
            if (q.size() == k) {  // 堆内已凑满 k 个人，再往里加就会超员
                tot -= q.top();  // 去掉速度最小者，让留下的人速度和最大
                q.pop();  // 同步把它弹出堆
            }  // 满员处理结束
        }  // 所有候选下限枚举完毕
        return (int) (ans % mod);  // 取模后返回；中间用 long long 防止乘积溢出
    }  // maxPerformance 结束
};  // Solution 类结束