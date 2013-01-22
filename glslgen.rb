# coding: utf-8

require 'erb'

def generate i, h
    if i.to_i > 4 then
        puts "#error code generator failed"
    end

    hh = Array.new

    h.each_index do |b|
        hh << {}
        i.to_i.times do |n|
            a = h[b].shift
            hh[b][a[0]] = a[1]
        end
    end

    puts i
    puts
    puts h
    puts
    puts hh
    exit

    e = ERB.new <<TEMPLATE
#include <iostream>
#include <vector>
#include <exception>

class vec<%= i %>
{
    public:
        typedef std::pair<vec<%= i %>*, std::vector<double>(vec<%= i %>::*)()> selection;
        <% hh.each do |b| %><% (1..b.size).each do |n| %><% b.keys.to_a.repeated_permutation(n).to_a.each do |k| %>
        selection <%= k.join "" %>;<% end %><% end %><% end %>

    private:
        double <% (1...#{i}).each do |n| %>_<%= n %>, <% end %>_<%= i %>;
        <% hh.each do |b| %><% (1..b.size).each do |n| %><% b.keys.to_a.repeated_permutation(n).to_a.each do |k| %>
        std::vector<double> _get_<%= k.join "" %>() { std::vector<double> v; <% (0...n).each do |j| %>v.push_back(<%= b[k[j]] %>); <% end %>return v; }<% end end end %>

        void _init_selections() {<% hh.each do |b| %><% (1..b.size).each do |n| %><% b.keys.to_a.repeated_permutation(n).to_a.each do |k| %>
            <%= k.join "" %> = vec<%= i %>::selection(this, &vec<%= i %>::_get_<%= k.join "" %>);<% end end end %>
        }

    public:
        vec<%= i %>() : <% (1...#{i}).each do |n| %>_<%= n %>(0.0), <% end %>_<%= i %>(0.0) {
            _init_selections();
        }
        vec<%= i %>(vec<%= i %> &v) {
            _init_selections();<% (1..#{i}).each do |n| %>
            _<%= n %> = v._<%= n %>;<% end %>
        }
        <% (2..#{i}).each do |n| a = [ :D, :S ].repeated_permutation(n).to_a.delete_if do |e| e.count(:S) == 0 && e.count(:D) != #{i} end; a.each do |c| %>
        vec<%= i %>(<% _d = _s = 0; c.each_index do |p| if c[p].eql? :D then %><% _d += 1 %>double d<%= _d %><%= ", " unless p.eql? c.size - 1 %><% else %><% _s += 1 %>vec<%= i %>::selection &s<%= _s %><%= ", " unless p.eql? c.size - 1 %><% end end %>) {
            _init_selections();<% (1..c.count(:S)).each do |p| %>
            std::vector<double> v<%= p %> = ((s<%= p %>.first)->*(s<%= p %>.second))();<% end %><% if c.count(:S) > 0 then %><% if c.count(:S) > 1 then %><% _p = (1...#{i}).to_a.repeated_permutation(c.count(:S)).to_a.delete_if do |e| s = 0; e.each do |u| s += u end; s != (#{i} - c.count(:D)) end %><% _f = true; _p.each do |e| %>
            <%= "else " unless _f %>if (<% e.each_index do |u| %>v<%= u + 1 %>.size() == <%= e[u] %><%= " && " unless u.eql? e.size - 1 %><% end %>) {<% _d = _s = _i = 0; _i += 1; c.each_index do |p|
                    if c[p].eql? :D then _d += 1 %>
                    _<%= _i %> = d<%= _d %>;<% _i += 1; else _s += 1; (1..e[_s - 1]).each do |u| %>
                    _<%= _i %> = v<%= _s %>[<%= u - 1 %>];<% _i += 1; end end %><%end%>
            }<% _f = false; end %>
            else
                throw std::exception();<% else %>
            if (v1.size() != <%= #{i} - c.count(:D) %>)
                throw std::exception();<% _d = _s = 0; c.each_index do |p|
                        if c[p].eql? :D then _d += 1 %>
            _<%= p + 1 %> = d<%= _d %>;<% else (0...(#{i} - c.count(:D))).each do |s| _s += 1%>
            _<%= p + _s %> = v1[<%= s %>];<% end end end %><% end %><% else (1..c.count(:D)).each do |p| %><% if c.count(:D) == #{i} %>
            _<%= p %> = d<%= p %>;<% end end %><% end %>
        }<% end end %>
        ~vec<%= i %>() {}

        friend std::ostream &operator<<(std::ostream &o, vec<%= i %> v);
};

std::ostream &operator<<(std::ostream &o, vec<%= i %> v) {
    o << "vec<%= i %>( " << <% (1...#{i}).each do |n| %>v._<%= n %> << ", " << <% end %>v._<%= i %> << ")";
    return o;
}

std::ostream &operator<<(std::ostream &o, vec<%= i %>::selection s) {
    std::vector<double> v = ((s.first)->*(s.second))();
    if (v.size() == 1)
        o << "double( ";
    else
        o << "vec" << v.size() << "( ";
    for (std::vector<double>::iterator i = v.begin(); i != v.end();) {
        o << *i;
        i++;
        if (i != v.end())
            o << ", ";
    }
    o << " )";
    return o;
}
TEMPLATE

    puts e.result binding
end

generate 2, [ { :x => :_1, :y => :_2, :z => :_3, :w => :_4}, { :r => :_1, :g => :_2, :b => :_3, :a => :_4 }, { :s => :_1, :t => :_2, :p => :_3, :q => :_4 } ]
generate 3, [ { :x => :_1, :y => :_2, :z => :_3, :w => :_4}, { :r => :_1, :g => :_2, :b => :_3, :a => :_4 }, { :s => :_1, :t => :_2, :p => :_3, :q => :_4 } ]
generate 4, [ { :x => :_1, :y => :_2, :z => :_3, :w => :_4}, { :r => :_1, :g => :_2, :b => :_3, :a => :_4 }, { :s => :_1, :t => :_2, :p => :_3, :q => :_4 } ]
