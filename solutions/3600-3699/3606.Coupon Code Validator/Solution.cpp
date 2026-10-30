// 3606. 优惠券校验器 / Coupon Code Validator
// 核心思路：先挑出同时满足“状态有效、业务类别合法、券码只含字母/数字/下划线”的下标，再按业务类别升序、券码升序排序后输出券码。
// 复杂度：时间 O(n log n)（排序主导），空间 O(n)，n 为优惠券数量。
class Solution {  // 定义题解类
public:  // 公有接口部分
    vector<string> validateCoupons(vector<string>& code, vector<string>& businessLine, vector<bool>& isActive) {  // 主函数：入参为券码、业务类别、是否有效三个平行数组
        vector<int> idx;  // 记录通过校验的券码下标
        unordered_set<string> bs = {"electronics", "grocery", "pharmacy", "restaurant"};  // 四种合法的业务类别

        for (int i = 0; i < code.size(); ++i) {  // 逐张遍历优惠券
            const string& c = code[i];  // 取出当前券码
            const string& b = businessLine[i];  // 取出当前券对应的业务类别
            bool a = isActive[i];  // 取出当前券的有效状态
            if (a && bs.count(b) && check(c)) {  // 三项校验全部通过才算是可用券
                idx.push_back(i);  // 把该券的下标保存下来
            }  // 条件分支结束
        }  // 遍历结束

        sort(idx.begin(), idx.end(), [&](int i, int j) {  // 对候选下标按题目要求排序
            if (businessLine[i] != businessLine[j]) return businessLine[i] < businessLine[j];  // 业务类别不同时，按类别字典序升序
            return code[i] < code[j];  // 类别相同时，按券码字典序升序
        });  // 排序调用结束

        vector<string> ans;  // 存放最终要输出的券码
        for (int i : idx) {  // 按排好序的下标依次取出
            ans.push_back(code[i]);  // 把券码追加到答案数组
        }  // 遍历结束
        return ans;  // 返回排好序的合法券码
    }  // 主函数结束

private:  // 私有辅助函数部分
    bool check(const string& s) {  // 判断券码是否只由字母、数字、下划线组成
        if (s.empty()) return false;  // 空串不算合法券码
        for (char c : s) {  // 逐个字符检查
            if (!isalnum(c) && c != '_') {  // 出现非字母、非数字、非下划线的字符即非法
                return false;  // 直接返回不合法
            }  // 条件分支结束
        }  // 循环结束
        return true;  // 全部字符都合法
    }  // 辅助函数结束
};  // 类定义结束
