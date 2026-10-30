// 题目：1299. 将每个元素替换为右侧最大元素（Replace Elements with Greatest Element on Right Side）
// 思路：从右往左遍历，用 mx 维护已扫过的右侧最大值，先把当前位置写成 mx，再用原值更新 mx。
// 时间复杂度：O(n)，每个元素只访问一次；空间复杂度：O(1)，除返回数组外只用常数变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> replaceElements(vector<int>& arr) {  // arr：待替换的数组
        for (int i = arr.size() - 1, mx = -1; ~i; --i) {  // i 从最右端向左；~i 等价于 i != -1；mx 是右侧最大值
            int x = arr[i];  // 先保存原值，稍后更新 mx 要用
            arr[i] = mx;  // 把当前元素替换成它右侧的最大值
            mx = max(mx, x);  // 用原值更新右侧最大值，供更左边的元素使用
        }
        return arr;  // 返回原地修改后的数组
    }
};
