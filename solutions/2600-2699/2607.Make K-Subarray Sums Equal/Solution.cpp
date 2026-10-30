// 题目：2607. 使子数组元素和相等（Make K-Subarray Sums Equal）
// 思路：把下标按 g = gcd(n, k) 分成若干同余类，同一类里的元素必须相等；每类取中位数作为目标值，累加绝对差即为最小代价。
// 时间复杂度：O(n log n)，类内排序的总代价不超过 O(n log n)；空间复杂度：O(n)，临时数组最多保存一整类元素。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    long long makeSubKSumEqual(vector<int>& arr, int k) {  // arr：输入数组；k：子数组长度；返回最小代价
        int n = arr.size();  // n：数组长度
        int g = gcd(n, k);  // g = gcd(n, k)：下标同余类的个数
        long long ans = 0;  // ans：累计的最小总代价，用 long long 防止溢出
        for (int i = 0; i < g; ++i) {  // 依次处理每个同余类
            vector<int> t;  // t：收集当前同余类中的所有元素
            for (int j = i; j < n; j += g) {  // 步长为 g，正好遍历完一个同余类 i, i+g, i+2g, ...
                t.push_back(arr[j]);  // 把该元素放入临时数组
            }  // 内层循环结束，得到一个完整的同余类
            sort(t.begin(), t.end());  // 排序，方便取中位数
            int mid = t[t.size() / 2];  // 中位数是让绝对差之和最小的目标值
            for (int x : t) {  // 遍历该同余类的每个元素
                ans += abs(x - mid);  // 累加把它改成中位数的代价
            }  // 元素遍历结束
        }  // 同余类遍历结束
        return ans;  // 返回总的最小代价
    }  // 方法结束
};  // 类定义结束