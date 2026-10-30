// 题目：1354. 多次求和构造目标数组（Construct Target Array With Multiple Sums）
// 思路：倒推。设最大元素为 mx、其余元素之和为 t，则 mx 必由 t 反复累加而来，故把 mx 一次性换成 mx % t（整除时取 t），直到堆顶变成 1。
// 时间复杂度：O(n log n + n log(max))，取模让最大值快速下降；空间复杂度：O(n)。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool isPossible(vector<int>& target) {  // 判断 target 能否由「全 1 数组、每次把某个元素替换为当前总和」构造出来
        priority_queue<int> pq;  // 大根堆：每次都要取出当前最大值做倒推
        long long s = 0;  // 记录所有元素之和，倒推时要用它算「其余元素之和」
        for (int i = 0; i < target.size(); i++) {  // 初始化：元素全部入堆并累加总和
            s += target[i];  // 累加总和
            pq.push(target[i]);  // 元素入大根堆
        }  // 初始化完成
        while (pq.top() != 1) {  // 堆顶仍是大于 1 的数，说明还能继续往上倒推
            int mx = pq.top();  // 取出当前最大值
            pq.pop();  // 先弹出，倒推出新值后再放回
            long long t = s - mx;  // t 是其余元素之和，也正是上一步被反复加上的那个总和
            if (t < 1 || mx - t < 1) {  // 其余元素为空，或 mx 减一次 t 后不再是正数，说明这个状态不可能出现
                return false;  // 该数组无法由全 1 构造出来
            }  // 合法性检查通过
            int x = mx % t;  // 一次跳过多次加法：mx 反复减 t 直到不超过 t 为止
            if (x == 0) {  // 整除时取模结果是 0，但元素必须至少为 1
                x = t;  // 把 0 修正为 t，保证元素取值合法
            }  // 修正完成
            pq.push(x);  // 把倒推得到的新值放回堆中
            s = s - mx + x;  // 同步更新总和：先去掉 mx，再加上新值 x
        }  // 堆顶变成 1，说明已经倒推到起始的全 1 数组
        return true;  // 能顺利倒推到全 1，说明 target 可以被构造出来
    }  // isPossible 结束
};  // 类定义结束