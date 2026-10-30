// 题目：1346. 检查整数及其两倍数是否存在（Check If N and Its Double Exist）
// 思路：顺序扫描并用哈希集合记录已经见过的数；对当前 x，检查 2x 是否已存在，以及 x 为偶数时 x/2 是否已存在（这样自动满足下标 i != j）。
// 时间复杂度：O(n)，每个元素只做两次哈希查询；空间复杂度：O(n)，哈希集合最多存 n 个数。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool checkIfExist(vector<int>& arr) {  // arr：输入数组，判断是否存在 i != j 使 arr[i] == 2 * arr[j]
        unordered_set<int> s;  // 哈希集合，保存已经遍历过的数
        for (int x : arr) {  // 按顺序遍历每个元素 x
            if (s.contains(x * 2) || (x % 2 == 0 && s.contains(x / 2))) {  // Two Sum 式查询：已有的数里有没有 2x，或者（x 是偶数时）有没有 x/2
                return true;  // 一旦命中就立刻返回 true
            }  // if 结束
            s.insert(x);  // 当前数先存起来，供后面的元素查询，保证用到的是不同下标
        }  // 遍历结束
        return false;  // 没有找到任何满足条件的一对数，返回 false
    }  // 方法结束
};  // 类定义结束（源文件为 CRLF 换行且末尾无换行，逐字节保持不变）