// 题目：2782. 唯一类别的数量（Number of Unique Categories）
// 核心思路：并查集。枚举所有下标对 (a, b) 用判题器接口询问是否同类，同类就合并两集合；最后统计父指针指向自身的根结点个数，即类别数量。
// 时间复杂度：O(n^2 * α(n))，n^2 次询问、每次合并近似 O(1)；空间复杂度：O(n)，父指针数组。
/**
 * Definition for a category handler.
 * class CategoryHandler {
 * public:
 *     CategoryHandler(vector<int> categories);
 *     bool haveSameCategory(int a, int b);
 * };
 */
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int numberOfCategories(int n, CategoryHandler* categoryHandler) {  // n：元素个数；categoryHandler：判题器提供的“同类判定”接口；返回不同类别的数量
        vector<int> p(n);  // p 是并查集的父指针数组，先给每个元素各自开一个集合
        iota(p.begin(), p.end(), 0);  // iota 把 p 填成 0,1,2,...,n-1：初始时每个下标都是自己集合的根
        function<int(int)> find = [&](int x) {  // 带路径压缩的递归 find；用 function 保存 lambda，是为了能在 lambda 内部递归调用自己
            if (p[x] != x) {  // 当前结点不是根，就要顺着父指针往上找
                p[x] = find(p[x]);  // 递归找到根，顺手把 p[x] 直接挂到根上，实现路径压缩
            }  // if 分支结束
            return p[x];  // 返回找到的根结点
        };  // lambda 定义结束
        for (int a = 0; a < n; ++a) {  // 枚举左元素 a
            for (int b = a + 1; b < n; ++b) {  // 只枚举 b > a 的对，避免重复询问同一对元素
                if (categoryHandler->haveSameCategory(a, b)) {  // 询问判题器：a 与 b 是否属于同一类别
                    p[find(a)] = find(b);  // 同类就合并两个集合：把 a 的根挂到 b 的根下面
                }  // if 分支结束
            }  // 内层循环结束
        }  // 外层循环结束
        int ans = 0;  // ans 统计根的个数，根的数量就是类别数
        for (int i = 0; i < n; ++i) {  // 遍历每个结点
            ans += i == p[i];  // 只有 p[i] == i 的结点才是根，才代表一个独立类别
        }  // 循环结束
        return ans;  // 返回类别数量
    }  // 方法结束
};  // 类定义结束