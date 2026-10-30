// 题目：2164. 对奇偶下标分别排序（Sort Even and Odd Indices Independently）
// 思路：把偶数下标元素收进 a 升序排、奇数下标元素收进 b 降序排，再按下标位置交替写回结果数组。
// 时间复杂度：O(n log n)，两次排序共处理 n 个元素；空间复杂度：O(n)，a、b 与结果数组都要额外空间。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> sortEvenOdd(vector<int>& nums) {  // nums：输入数组；返回各下标按要求排好序的新数组
        int n = nums.size();  // n：数组长度，后面创建结果数组要用
        vector<int> a;  // a：存放所有偶数下标（0、2、4…）上的元素
        vector<int> b;  // b：存放所有奇数下标（1、3、5…）上的元素
        for (int i = 0; i < n; ++i) {  // 第一趟遍历：按下标奇偶把元素分流到两个数组
            if (i % 2 == 0) {  // 下标为偶数，走 a 分支
                a.push_back(nums[i]);  // 把当前偶数下标元素追加到 a
            } else {  // 否则下标为奇数，走 b 分支
                b.push_back(nums[i]);  // 把当前奇数下标元素追加到 b
            }  // if/else 结束
        }  // 遍历结束，a、b 已按原顺序装好各自的元素
        sort(a.begin(), a.end());  // 偶数下标要求非递减，所以把 a 升序排序
        sort(b.rbegin(), b.rend());  // 奇数下标要求非递增，用反向迭代器让 b 降序
        vector<int> ans(n);  // 结果数组长度与输入相同，先开好空间再逐位填充
        for (int i = 0, j = 0; j < a.size(); i += 2, ++j) {  // i 从 0 每次 +2 只走偶数下标，j 依次取 a 中元素
            ans[i] = a[j];  // 把 a[j] 放回第 i 个（偶数）位置
        }  // 偶数位填充完毕
        for (int i = 1, j = 0; j < b.size(); i += 2, ++j) {  // i 从 1 每次 +2 只走奇数下标，j 依次取 b 中元素
            ans[i] = b[j];  // 把 b[j] 放回第 i 个（奇数）位置
        }  // 奇数位填充完毕
        return ans;  // 返回重排后的数组
    }  // 方法结束
};  // 类定义结束