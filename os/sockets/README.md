On Redhat 2017:
sudo iptables -A CUSTOM -s 147.138.0.0/17 -p tcp --dport 8896 -j ACCEPT

On CENTOS 2019:  
firewall-cmd --add-rich-rule='rule family="ipv4" source address="147.138.0.0/17" port port="8896" protocol="tcp" accept'
firewall-cmd --reload
