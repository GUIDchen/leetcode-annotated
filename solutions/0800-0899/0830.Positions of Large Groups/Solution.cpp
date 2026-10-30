// 题目：830. 较大分组的位置（Positions of Large Groups）
// 思路：双指针扫描。i 指向当前分组的起点，j 一路右移找到分组末尾，长度 >= 3 就记录 [i, j-1]，然后 i 跳到 j 继续下一组。
// 时间复杂度：O(n)，每个字符只被访问一次；空间复杂度：O(1)（不计返回结果占用的空间）。
class Solution {  // LeetCode 约定的题解类
public:  // 方法对外可见
    vector<vector<int>> largeGroupPositions(string s) {  // s 是只含小写字母的字符串，返回所有长度 >= 3 的连续相同字符分组的起止下标
        int n = s.size();  // 字符串长度
        int i = 0;  // 当前分组的起点下标
        vector<vector<int>> ans;  // 结果数组，元素是 [start, end]
        while (i < n) {  // 只要还没扫完，就处理一个分组
            int j = i;  // j 从分组起点开始，用来寻找分组末尾的下一位
            while (j < n && s[j] == s[i]) {  // 一直右移，直到越界或者字符与分组首字符不同
                ++j;  // 字符仍然相同，末尾后移
            }  // 结束内层扫描，此时 [i, j-1] 是一个完整分组
            if (j - i >= 3) {  // 长度 j-i 至少为 3 才算较大分组
                ans.push_back({i, j - 1});  // 记录这一组的起止下标（右端是 j-1 而不是 j）
            }  // 结束 if
            i = j;  // 从下一个分组继续，直接从 j 开始即可
        }  // 结束外层循环
        return ans;  // 返回所有较大分组的位置
    }  // 结束方法
};  // 结束类