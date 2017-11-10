'''
Created on Sep 24, 2014

@author: Alexandre
'''
from _pytest.runner import fail

def enum(**enums):
    return type('Enum', (), enums)
#end enum


SockType = enum(
    Stream   = 's',
    Datagram = 'd'
)


AddrFamily = enum(
    IPv4 = '4',
    IPv6 = '6'
)   
    
class netcmd:        
    
    def  __init__ (self, io):
        self.io = io
        #end __init__()  
    
    
    def RouteAdd (self, if_nbr, addr, mask, gateway, addr_family):        
        
        family = self._getAddrFamily(addr_family)
        if (family == None):
            return (False, "Invalid address Family")
        
        result, rd = self._IO_ExecCmd("net_route_add -i " + if_nbr + " -" + family + " " + addr + " " + mask + " " + gateway)    
        
        return (result, rd)
    #end RouteAdd()
    
    
    
    def RouteRemove (self, if_nbr, addr, mask, gateway, addr_family):   
        family = self._getAddrFamily(addr_family)
        if (family == None):
            return (False, "Invalid address Family")
        
        result, rd = self._IO_ExecCmd("net_route_remove -i " + if_nbr + " -" + family + " " + addr + " " + mask + " " + gateway)    
        
        return (result)    
    #end RouteRemove()
    
    
    
    def SockOpen (self, sock_type, addr_family):
        
        sock_id = "0"
        
        
        family = self._getAddrFamily(addr_family)
        if (family == None):
            return (False, "Invalid address Family")
        
        type = self._getSockType(sock_type)
        if (type == None):
            return (False, "Invalid Socket Type")
            
            
        family = AddrFamily.IPv4
        addr_family = addr_family.lower()
        if addr_family.find("ipv4") > -1:
           family = AddrFamily.IPv4
        elif addr_family.find("ipv6") > -1:
            family = AddrFamily.IPv6
        else: 
            return (False, "Invalid address Family", sock_id)
                     
             
        result, rd = self._IO_ExecCmd("net_sock_open -t " + type + " -f " + family)    
        if (result == True):
            sock_id = self._extractSockID(rd)
            
            
        return (result, sock_id, rd)
    #end sockOpen()
    
        
        
    def SockClose (self, sock_id):        
        
        result, rd = self._IO_ExecCmd("net_sock_close -i " +  sock_id)
        
        return (result, rd)    
    #end sockClose()
    
    
    
    def SockBind (self, sock_id, port):
        
        
        result, rd = self._IO_ExecCmd("net_sock_bind -i " +  sock_id + " -f 4 -p " + str(port))
        
        return (result, rd)    
    #end sockBind()
    
    
    
    def SockListen (self, sock_id, queue_size):
        
        result, rd = self._IO_ExecCmd("net_sock_listen -i " +  sock_id + " -q " + str(queue_size)) 
        
        return (result, rd) 
    #end sockListen()
    
    
    
    def SockAccept (self, sock_id):
        
        result, rd = self._IO_ExecCmd("net_sock_accept -i " +  sock_id)
        if (result == True):
            sock_id = self._extractSockID(rd)
        
        return (result, sock_id, rd)
    #end sockAccept()
    
    
    
    def SockConnect (self, sock_id, addr, port):
        
        result, rd = self._IO_ExecCmd("net_sock_connect -i " +  sock_id + " -a " + addr + " -p " + str(port))

        
        return (result, rd)
    #end netCmdSockConnect()
    
    
    def SockOptSetChild (self, sock_id, child_count):    
        result, rd = self._IO_ExecCmd("net_sock_opt_set_child -i " +  sock_id + " -v " + str(child_count))

        
        return (result, rd)
    #end netCmdSockConnect()
    
    
    
    def Ping (self, addr):
        
        result, val = self._IO_ExecCmd("net_ping " +  addr)
        
        return (result)
    #end netCmdSockConnect()    
    
    
    
    def _IO_ExecCmd (self, cmd_str):        
        cmd_list = list()
        cmd_list.append(cmd_str)
        line_list = self.io.Command(cmd_list)
        
        for line in line_list:
            val = line.replace('\r\n','\n').replace('\r','\n')
            print (val)
            
            if val.find("Error") > -1: 
                return (False, val)            
        #end for
                
        return (True, val)
    #end _IO_ExecCmd()    
    
    
    
    def _extractSockID(self, str_val):
        sock_ix = str_val.find("Socket ID = \n")
        sock_ix += len("Socket ID = \n")
        sock_id = str_val[sock_ix:]
        end = sock_id.find('\n')
        sock_id = sock_id[: end]
        return sock_id
    #end _extractSockID()    
    
    
    
    def _getSockType (self, sock_type_str):
        type = SockType.Stream
        
        sock_type = sock_type_str.lower()
        if sock_type.find("stream") > -1:
           type = SockType.Stream
        elif sock_type.find("datagram") > -1:
            type = SockType.Datagram
        else:
            return None
        
        
        return type
    #end _getAddrFamily()
    
    
    
    def _getAddrFamily (self, family_str):
        family = AddrFamily.IPv4
        
        addr_family = family_str.lower()
        if addr_family.find("ipv4") > -1:
           family = AddrFamily.IPv4
        elif addr_family.find("ipv6") > -1:
            family = AddrFamily.IPv6
        else: 
            return (None)
        
        return family
    #end _getAddrFamily()
    
#end  class NetCmd