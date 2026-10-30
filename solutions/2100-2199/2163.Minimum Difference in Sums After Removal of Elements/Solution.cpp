// 题目：2163. 删除元素后和的最小差值（Minimum Difference in Sums After Removal of Elements）
// 核心思路：预处理 pre[i]（前 i 个元素里选 n 个的最小和）与 suf[i]（后缀 i 起选 n 个的最大和），再枚举分界点最小化 pre[i] - suf[i+1]。
// 时间复杂度：O(m log n)，m 为数组长度；空间复杂度：O(m)，两个前缀/后缀数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    long long minimumDifference(vector<int>& nums) {  // nums：长度是 3 的倍数的数组
        int m = nums.size();  // 数组总长度
        int n = m / 3;  // 三等分后每份要取的元素个数

        using ll = long long;  // 简化类型名，避免求和溢出
        ll s = 0;  // 堆内元素之和，也就是当前最小的 n 个数之和
        ll pre[m + 1];  // pre[i]：前 i 个元素中选 n 个能得到的最小和
        priority_queue<int> q1;  // 大根堆，用来把最大的元素挤出去，只保留最小的 n 个
        for (int i = 1; i <= n * 2; ++i) {  // 第一份的分界最多到 2n，给后面留出 n 个元素
            int x = nums[i - 1];  // 当前元素（下标转成 0 起始）
            s += x;  // 先无条件加入累加
            q1.push(x);  // 放进大根堆
            if (q1.size() > n) {  // 堆内元素超过 n 个
                s -= q1.top();  // 减去堆顶最大值，保持堆内 n 个元素之和最小
                q1.pop();  // 同步把堆顶弹出
            }  // 调整结束
            pre[i] = s;  // 记录前 i 个元素选 n 个的最小和
        }  // 前缀扫描结束
        s = 0;  // 复用累加变量，开始计算后缀
        ll suf[m + 1];  // suf[i]：从第 i 个元素到末尾选 n 个能得到的最大和
        priority_queue<int, vector<int>, greater<int>> q2;  // 小根堆，用来把最小的元素挤出去，只保留最大的 n 个
        for (int i = m; i > n; --i) {  // 从右往左扫，必须给第一份留出 n 个位置
            int x = nums[i - 1];  // 当前元素（下标转成 0 起始）
            s += x;  // 先无条件加入累加
            q2.push(x);  // 放进小根堆
            if (q2.size() > n) {  // 堆内元素超过 n 个
                s -= q2.top();  // 减去堆顶最小值，保持堆内 n 个元素之和最大
                q2.pop();  // 同步把堆顶弹出
            }  // 调整结束
            suf[i] = s;  // 记录后缀选 n 个的最大和
        }  // 后缀扫描结束
        ll ans = 1e18;  // 答案初始化为一个足够大的数
        for (int i = n; i <= n * 2; ++i) {  // 枚举分界点：左边至少 n 个、右边至少 n 个
            ans = min(ans, pre[i] - suf[i + 1]);  // 左边最小和减去右边最大和，取差值最小者
        }  // 枚举结束
        return ans;  // 返回最小差值
    }  // 方法结束
};  // 题解类定义结束