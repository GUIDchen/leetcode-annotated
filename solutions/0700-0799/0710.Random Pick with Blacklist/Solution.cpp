// 题目：710. 黑名单中的随机数（Random Pick with Blacklist）
// 思路：令 k = n - |blacklist|，把 [0, k) 视作压缩后的白名单区；若其中某些位置本身在黑名单里，就用尾部 [k, n) 中的合法位置替换它们并记录映射，之后只需在 [0, k) 上均匀随机。
// 时间复杂度：构造 O(b)，b 为黑名单长度，pick 为 O(1)；空间复杂度：O(b)，哈希表最多保存 b 条映射。
class Solution {  // 随机取数类
public:  // 对外接口：构造函数与 pick 方法
    unordered_map<int, int> d;  // 映射表：落在 [0, k) 的黑名单下标，映射到 [k, n) 中的某个合法下标
    int k;  // 随机范围上限，[0, k) 是压缩后的白名单区

    Solution(int n, vector<int>& blacklist) {  // 构造函数：n 是数字范围 [0, n)，blacklist 是不能选的数
        k = n - blacklist.size();  // 白名单区大小：总共 n 个数去掉黑名单里的数
        int i = k;  // i 从 k 开始，作为可交换的尾部位置指针
        unordered_set<int> black(blacklist.begin(), blacklist.end());  // 把黑名单转成哈希集合，便于 O(1) 判断某个数是否被禁用
        for (int& b : blacklist) {  // 只处理落在白名单区 [0, k) 内的黑名单元素，它们必须被替换
            if (b < k) {  // 该黑名单元素位于白名单区，需要换成尾部的一个合法位置
                while (black.count(i)) ++i;  // 向后跳过同样被禁用的位置，找到第一个可用的合法位置
                d[b] = i++;  // 建立映射：原本取到 b 时改取 i，随后 i 后移避免重复使用
            }
        }  // 构造函数结束
    }

    int pick() {  // 随机返回一个不在黑名单中的数
        int x = rand() % k;  // 在压缩后的白名单区 [0, k) 内均匀取一个随机下标
        return d.count(x) ? d[x] : x;  // 该下标被映射过就返回替换值，否则它本身就是白名单中的合法下标
    }
};  // 类定义结束

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(n, blacklist);
 * int param_1 = obj->pick();
 */