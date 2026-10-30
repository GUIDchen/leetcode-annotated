// 题目：2391. 收集垃圾的最少总时间（Minimum Amount of Time to Collect Garbage）
// 思路：垃圾件数必捡；每种垃圾只需让车开到最后一次出现它的房子，用前缀和累加行驶时间。
// 时间复杂度：O(n + L)，L 为垃圾字符总数；空间复杂度：O(1)，last 最多存 3 种垃圾。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int garbageCollection(vector<string>& garbage, vector<int>& travel) {  // garbage：每间房子的垃圾字符串；travel：相邻房子之间的行驶耗时
        unordered_map<char, int> last;  // 哈希表「垃圾种类 → 最后一次出现的房子下标」，用来确定车最远开到哪里
        int ans = 0;  // 答案：捡垃圾的件数（每件 1 单位时间）+ 车辆行驶耗时
        for (int i = 0; i < garbage.size(); ++i) {  // 第一遍：逐间房子统计垃圾件数，并记录每种垃圾最后出现的房子下标
            auto& s = garbage[i];  // 当前房子的垃圾字符串（引用绑定，避免字符串拷贝）
            ans += s.size();  // 每件垃圾都要停留 1 单位时间，所以直接累加字符个数
            for (char& c : s) {  // 逐字符扫描，字符本身就是垃圾种类 'M' / 'P' / 'G'
                last[c] = i;  // 不断覆盖，循环结束后 last[c] 就是该种垃圾最后一次出现的房子下标
            }  // 字符循环结束
        }  // 房子循环结束
        int ts = 0;  // 车辆行驶时间的累计前缀和：从 0 号房开到当前 i 号房的总耗时
        for (int i = 1; i <= travel.size(); ++i) {  // 第二遍：枚举每一段路（i 号房对应 travel[i-1]），把需要的路程计入答案
            ts += travel[i - 1];  // 前缀和累加：ts 表示从 0 号房开到 i 号房的总时间
            for (auto& [_, j] : last) {  // 结构化绑定遍历「垃圾种类 → 最后出现下标」，_ 表示用不到的字符
                if (i == j) {  // 当前房子正好是某种垃圾最后出现的位置，说明为该垃圾必须开到这里
                    ans += ts;  // 加上这趟车程；前缀和保证每辆车只走一条单向路线，不重复计算
                }  // if 判断结束
            }  // 垃圾种类循环结束
        }  // 路段循环结束
        return ans;  // 返回捡垃圾的总时间
    }  // 方法结束
};  // 题解类结束