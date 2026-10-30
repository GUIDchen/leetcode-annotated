// 题目：658. 找到 K 个最接近的元素（Find K Closest Elements）
// 核心思路：按「与 x 的距离」升序排序后取前 k 个，再按数值升序输出（距离相同取较小值）。
// 时间复杂度：O(n log n)（两次排序）；空间复杂度：O(k) 存放结果。
int target;  // 全局变量：把目标值 x 传给比较器（cmp 是静态函数，无法捕获外部变量）

class Solution {  // LeetCode 约定的题解类
public:
    static bool cmp(int& a, int& b) {  // 排序比较器：离 x 更近的排前面
        int v = abs(a - target) - abs(b - target);  // v 是两者与 x 的距离之差，等于 0 表示距离相同
        return v == 0 ? a < b : v < 0;  // 距离相同按数值升序，否则距离小的排前面
    }

    vector<int> findClosestElements(vector<int>& arr, int k, int x) {  // arr 已升序，k 是要取的个数，x 是目标值
        target = x;  // 先把目标值写入全局变量，供 cmp 使用
        sort(arr.begin(), arr.end(), cmp);  // 按「离 x 的距离」升序重排整个数组（sort 对相等元素不保证顺序，由 cmp 兜住）
        vector<int> ans(arr.begin(), arr.begin() + k);  // 取前 k 个就是距离最近的集合
        sort(ans.begin(), ans.end());  // 题目要求结果按升序返回，所以再排一次
        return ans;  // 返回结果数组
    }
};  // 题解类定义结束