
echo:     file format elf64-x86-64


Disassembly of section .init:

0000000000001000 <_init>:
    1000:	48 83 ec 08          	sub    $0x8,%rsp
    1004:	48 8b 05 dd 2f 00 00 	mov    0x2fdd(%rip),%rax        # 3fe8 <__gmon_start__>
    100b:	48 85 c0             	test   %rax,%rax
    100e:	74 02                	je     1012 <_init+0x12>
    1010:	ff d0                	callq  *%rax
    1012:	48 83 c4 08          	add    $0x8,%rsp
    1016:	c3                   	retq   

Disassembly of section .plt:

0000000000001020 <.plt>:
    1020:	ff 35 e2 2f 00 00    	pushq  0x2fe2(%rip)        # 4008 <_GLOBAL_OFFSET_TABLE_+0x8>
    1026:	ff 25 e4 2f 00 00    	jmpq   *0x2fe4(%rip)        # 4010 <_GLOBAL_OFFSET_TABLE_+0x10>
    102c:	0f 1f 40 00          	nopl   0x0(%rax)

0000000000001030 <write@plt>:
    1030:	ff 25 e2 2f 00 00    	jmpq   *0x2fe2(%rip)        # 4018 <write@GLIBC_2.2.5>
    1036:	68 00 00 00 00       	pushq  $0x0
    103b:	e9 e0 ff ff ff       	jmpq   1020 <.plt>

Disassembly of section .plt.got:

0000000000001040 <__cxa_finalize@plt>:
    1040:	ff 25 b2 2f 00 00    	jmpq   *0x2fb2(%rip)        # 3ff8 <__cxa_finalize@GLIBC_2.2.5>
    1046:	66 90                	xchg   %ax,%ax

Disassembly of section .text:

0000000000001050 <_start>:
    1050:	31 ed                	xor    %ebp,%ebp
    1052:	49 89 d1             	mov    %rdx,%r9
    1055:	5e                   	pop    %rsi
    1056:	48 89 e2             	mov    %rsp,%rdx
    1059:	48 83 e4 f0          	and    $0xfffffffffffffff0,%rsp
    105d:	50                   	push   %rax
    105e:	54                   	push   %rsp
    105f:	4c 8d 05 ba 03 00 00 	lea    0x3ba(%rip),%r8        # 1420 <__libc_csu_fini>
    1066:	48 8d 0d 53 03 00 00 	lea    0x353(%rip),%rcx        # 13c0 <__libc_csu_init>
    106d:	48 8d 3d a5 02 00 00 	lea    0x2a5(%rip),%rdi        # 1319 <main>
    1074:	ff 15 66 2f 00 00    	callq  *0x2f66(%rip)        # 3fe0 <__libc_start_main@GLIBC_2.2.5>
    107a:	f4                   	hlt    
    107b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

0000000000001080 <deregister_tm_clones>:
    1080:	48 8d 3d a9 2f 00 00 	lea    0x2fa9(%rip),%rdi        # 4030 <__TMC_END__>
    1087:	48 8d 05 a2 2f 00 00 	lea    0x2fa2(%rip),%rax        # 4030 <__TMC_END__>
    108e:	48 39 f8             	cmp    %rdi,%rax
    1091:	74 15                	je     10a8 <deregister_tm_clones+0x28>
    1093:	48 8b 05 3e 2f 00 00 	mov    0x2f3e(%rip),%rax        # 3fd8 <_ITM_deregisterTMCloneTable>
    109a:	48 85 c0             	test   %rax,%rax
    109d:	74 09                	je     10a8 <deregister_tm_clones+0x28>
    109f:	ff e0                	jmpq   *%rax
    10a1:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)
    10a8:	c3                   	retq   
    10a9:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)

00000000000010b0 <register_tm_clones>:
    10b0:	48 8d 3d 79 2f 00 00 	lea    0x2f79(%rip),%rdi        # 4030 <__TMC_END__>
    10b7:	48 8d 35 72 2f 00 00 	lea    0x2f72(%rip),%rsi        # 4030 <__TMC_END__>
    10be:	48 29 fe             	sub    %rdi,%rsi
    10c1:	48 89 f0             	mov    %rsi,%rax
    10c4:	48 c1 ee 3f          	shr    $0x3f,%rsi
    10c8:	48 c1 f8 03          	sar    $0x3,%rax
    10cc:	48 01 c6             	add    %rax,%rsi
    10cf:	48 d1 fe             	sar    %rsi
    10d2:	74 14                	je     10e8 <register_tm_clones+0x38>
    10d4:	48 8b 05 15 2f 00 00 	mov    0x2f15(%rip),%rax        # 3ff0 <_ITM_registerTMCloneTable>
    10db:	48 85 c0             	test   %rax,%rax
    10de:	74 08                	je     10e8 <register_tm_clones+0x38>
    10e0:	ff e0                	jmpq   *%rax
    10e2:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)
    10e8:	c3                   	retq   
    10e9:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)

00000000000010f0 <__do_global_dtors_aux>:
    10f0:	80 3d 39 2f 00 00 00 	cmpb   $0x0,0x2f39(%rip)        # 4030 <__TMC_END__>
    10f7:	75 2f                	jne    1128 <__do_global_dtors_aux+0x38>
    10f9:	55                   	push   %rbp
    10fa:	48 83 3d f6 2e 00 00 	cmpq   $0x0,0x2ef6(%rip)        # 3ff8 <__cxa_finalize@GLIBC_2.2.5>
    1101:	00 
    1102:	48 89 e5             	mov    %rsp,%rbp
    1105:	74 0c                	je     1113 <__do_global_dtors_aux+0x23>
    1107:	48 8b 3d 1a 2f 00 00 	mov    0x2f1a(%rip),%rdi        # 4028 <__dso_handle>
    110e:	e8 2d ff ff ff       	callq  1040 <__cxa_finalize@plt>
    1113:	e8 68 ff ff ff       	callq  1080 <deregister_tm_clones>
    1118:	c6 05 11 2f 00 00 01 	movb   $0x1,0x2f11(%rip)        # 4030 <__TMC_END__>
    111f:	5d                   	pop    %rbp
    1120:	c3                   	retq   
    1121:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)
    1128:	c3                   	retq   
    1129:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)

0000000000001130 <frame_dummy>:
    1130:	e9 7b ff ff ff       	jmpq   10b0 <register_tm_clones>

0000000000001135 <noendln>:
    1135:	55                   	push   %rbp
    1136:	48 89 e5             	mov    %rsp,%rbp
    1139:	48 83 ec 20          	sub    $0x20,%rsp
    113d:	89 7d fc             	mov    %edi,-0x4(%rbp)
    1140:	48 89 75 f0          	mov    %rsi,-0x10(%rbp)
    1144:	48 89 55 e8          	mov    %rdx,-0x18(%rbp)
    1148:	48 89 4d e0          	mov    %rcx,-0x20(%rbp)
    114c:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
    1150:	8b 00                	mov    (%rax),%eax
    1152:	8d 50 01             	lea    0x1(%rax),%edx
    1155:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
    1159:	89 10                	mov    %edx,(%rax)
    115b:	e9 b1 00 00 00       	jmpq   1211 <noendln+0xdc>
    1160:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
    1164:	c7 00 00 00 00 00    	movl   $0x0,(%rax)
    116a:	eb 46                	jmp    11b2 <noendln+0x7d>
    116c:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
    1170:	8b 00                	mov    (%rax),%eax
    1172:	48 98                	cltq   
    1174:	48 8d 14 c5 00 00 00 	lea    0x0(,%rax,8),%rdx
    117b:	00 
    117c:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
    1180:	48 01 d0             	add    %rdx,%rax
    1183:	48 8b 10             	mov    (%rax),%rdx
    1186:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
    118a:	8b 00                	mov    (%rax),%eax
    118c:	48 98                	cltq   
    118e:	48 01 d0             	add    %rdx,%rax
    1191:	ba 01 00 00 00       	mov    $0x1,%edx
    1196:	48 89 c6             	mov    %rax,%rsi
    1199:	bf 01 00 00 00       	mov    $0x1,%edi
    119e:	e8 8d fe ff ff       	callq  1030 <write@plt>
    11a3:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
    11a7:	8b 00                	mov    (%rax),%eax
    11a9:	8d 50 01             	lea    0x1(%rax),%edx
    11ac:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
    11b0:	89 10                	mov    %edx,(%rax)
    11b2:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
    11b6:	8b 00                	mov    (%rax),%eax
    11b8:	48 98                	cltq   
    11ba:	48 8d 14 c5 00 00 00 	lea    0x0(,%rax,8),%rdx
    11c1:	00 
    11c2:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
    11c6:	48 01 d0             	add    %rdx,%rax
    11c9:	48 8b 10             	mov    (%rax),%rdx
    11cc:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
    11d0:	8b 00                	mov    (%rax),%eax
    11d2:	48 98                	cltq   
    11d4:	48 01 d0             	add    %rdx,%rax
    11d7:	0f b6 00             	movzbl (%rax),%eax
    11da:	84 c0                	test   %al,%al
    11dc:	75 8e                	jne    116c <noendln+0x37>
    11de:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
    11e2:	8b 00                	mov    (%rax),%eax
    11e4:	83 c0 01             	add    $0x1,%eax
    11e7:	39 45 fc             	cmp    %eax,-0x4(%rbp)
    11ea:	74 16                	je     1202 <noendln+0xcd>
    11ec:	ba 01 00 00 00       	mov    $0x1,%edx
    11f1:	48 8d 35 0c 0e 00 00 	lea    0xe0c(%rip),%rsi        # 2004 <_IO_stdin_used+0x4>
    11f8:	bf 01 00 00 00       	mov    $0x1,%edi
    11fd:	e8 2e fe ff ff       	callq  1030 <write@plt>
    1202:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
    1206:	8b 00                	mov    (%rax),%eax
    1208:	8d 50 01             	lea    0x1(%rax),%edx
    120b:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
    120f:	89 10                	mov    %edx,(%rax)
    1211:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
    1215:	8b 00                	mov    (%rax),%eax
    1217:	39 45 fc             	cmp    %eax,-0x4(%rbp)
    121a:	0f 8f 40 ff ff ff    	jg     1160 <noendln+0x2b>
    1220:	90                   	nop
    1221:	90                   	nop
    1222:	c9                   	leaveq 
    1223:	c3                   	retq   

0000000000001224 <normal>:
    1224:	55                   	push   %rbp
    1225:	48 89 e5             	mov    %rsp,%rbp
    1228:	48 83 ec 20          	sub    $0x20,%rsp
    122c:	89 7d fc             	mov    %edi,-0x4(%rbp)
    122f:	48 89 75 f0          	mov    %rsi,-0x10(%rbp)
    1233:	48 89 55 e8          	mov    %rdx,-0x18(%rbp)
    1237:	48 89 4d e0          	mov    %rcx,-0x20(%rbp)
    123b:	e9 b1 00 00 00       	jmpq   12f1 <normal+0xcd>
    1240:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
    1244:	c7 00 00 00 00 00    	movl   $0x0,(%rax)
    124a:	eb 46                	jmp    1292 <normal+0x6e>
    124c:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
    1250:	8b 00                	mov    (%rax),%eax
    1252:	48 98                	cltq   
    1254:	48 8d 14 c5 00 00 00 	lea    0x0(,%rax,8),%rdx
    125b:	00 
    125c:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
    1260:	48 01 d0             	add    %rdx,%rax
    1263:	48 8b 10             	mov    (%rax),%rdx
    1266:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
    126a:	8b 00                	mov    (%rax),%eax
    126c:	48 98                	cltq   
    126e:	48 01 d0             	add    %rdx,%rax
    1271:	ba 01 00 00 00       	mov    $0x1,%edx
    1276:	48 89 c6             	mov    %rax,%rsi
    1279:	bf 01 00 00 00       	mov    $0x1,%edi
    127e:	e8 ad fd ff ff       	callq  1030 <write@plt>
    1283:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
    1287:	8b 00                	mov    (%rax),%eax
    1289:	8d 50 01             	lea    0x1(%rax),%edx
    128c:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
    1290:	89 10                	mov    %edx,(%rax)
    1292:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
    1296:	8b 00                	mov    (%rax),%eax
    1298:	48 98                	cltq   
    129a:	48 8d 14 c5 00 00 00 	lea    0x0(,%rax,8),%rdx
    12a1:	00 
    12a2:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
    12a6:	48 01 d0             	add    %rdx,%rax
    12a9:	48 8b 10             	mov    (%rax),%rdx
    12ac:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
    12b0:	8b 00                	mov    (%rax),%eax
    12b2:	48 98                	cltq   
    12b4:	48 01 d0             	add    %rdx,%rax
    12b7:	0f b6 00             	movzbl (%rax),%eax
    12ba:	84 c0                	test   %al,%al
    12bc:	75 8e                	jne    124c <normal+0x28>
    12be:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
    12c2:	8b 00                	mov    (%rax),%eax
    12c4:	83 c0 01             	add    $0x1,%eax
    12c7:	39 45 fc             	cmp    %eax,-0x4(%rbp)
    12ca:	74 16                	je     12e2 <normal+0xbe>
    12cc:	ba 01 00 00 00       	mov    $0x1,%edx
    12d1:	48 8d 35 2c 0d 00 00 	lea    0xd2c(%rip),%rsi        # 2004 <_IO_stdin_used+0x4>
    12d8:	bf 01 00 00 00       	mov    $0x1,%edi
    12dd:	e8 4e fd ff ff       	callq  1030 <write@plt>
    12e2:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
    12e6:	8b 00                	mov    (%rax),%eax
    12e8:	8d 50 01             	lea    0x1(%rax),%edx
    12eb:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
    12ef:	89 10                	mov    %edx,(%rax)
    12f1:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
    12f5:	8b 00                	mov    (%rax),%eax
    12f7:	39 45 fc             	cmp    %eax,-0x4(%rbp)
    12fa:	0f 8f 40 ff ff ff    	jg     1240 <normal+0x1c>
    1300:	ba 01 00 00 00       	mov    $0x1,%edx
    1305:	48 8d 35 fa 0c 00 00 	lea    0xcfa(%rip),%rsi        # 2006 <_IO_stdin_used+0x6>
    130c:	bf 01 00 00 00       	mov    $0x1,%edi
    1311:	e8 1a fd ff ff       	callq  1030 <write@plt>
    1316:	90                   	nop
    1317:	c9                   	leaveq 
    1318:	c3                   	retq   

0000000000001319 <main>:
    1319:	55                   	push   %rbp
    131a:	48 89 e5             	mov    %rsp,%rbp
    131d:	48 83 ec 20          	sub    $0x20,%rsp
    1321:	89 7d ec             	mov    %edi,-0x14(%rbp)
    1324:	48 89 75 e0          	mov    %rsi,-0x20(%rbp)
    1328:	c7 45 fc 00 00 00 00 	movl   $0x0,-0x4(%rbp)
    132f:	c7 45 f8 00 00 00 00 	movl   $0x0,-0x8(%rbp)
    1336:	8b 45 fc             	mov    -0x4(%rbp),%eax
    1339:	83 c0 01             	add    $0x1,%eax
    133c:	89 45 fc             	mov    %eax,-0x4(%rbp)
    133f:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
    1343:	48 83 c0 08          	add    $0x8,%rax
    1347:	48 8b 00             	mov    (%rax),%rax
    134a:	0f b6 00             	movzbl (%rax),%eax
    134d:	3c 2d                	cmp    $0x2d,%al
    134f:	75 44                	jne    1395 <main+0x7c>
    1351:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
    1355:	48 83 c0 08          	add    $0x8,%rax
    1359:	48 8b 00             	mov    (%rax),%rax
    135c:	48 83 c0 01          	add    $0x1,%rax
    1360:	0f b6 00             	movzbl (%rax),%eax
    1363:	3c 6e                	cmp    $0x6e,%al
    1365:	75 2e                	jne    1395 <main+0x7c>
    1367:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
    136b:	48 83 c0 08          	add    $0x8,%rax
    136f:	48 8b 00             	mov    (%rax),%rax
    1372:	48 83 c0 02          	add    $0x2,%rax
    1376:	0f b6 00             	movzbl (%rax),%eax
    1379:	84 c0                	test   %al,%al
    137b:	75 18                	jne    1395 <main+0x7c>
    137d:	48 8d 4d f8          	lea    -0x8(%rbp),%rcx
    1381:	48 8d 55 fc          	lea    -0x4(%rbp),%rdx
    1385:	48 8b 75 e0          	mov    -0x20(%rbp),%rsi
    1389:	8b 45 ec             	mov    -0x14(%rbp),%eax
    138c:	89 c7                	mov    %eax,%edi
    138e:	e8 a2 fd ff ff       	callq  1135 <noendln>
    1393:	eb 16                	jmp    13ab <main+0x92>
    1395:	48 8d 4d f8          	lea    -0x8(%rbp),%rcx
    1399:	48 8d 55 fc          	lea    -0x4(%rbp),%rdx
    139d:	48 8b 75 e0          	mov    -0x20(%rbp),%rsi
    13a1:	8b 45 ec             	mov    -0x14(%rbp),%eax
    13a4:	89 c7                	mov    %eax,%edi
    13a6:	e8 79 fe ff ff       	callq  1224 <normal>
    13ab:	b8 00 00 00 00       	mov    $0x0,%eax
    13b0:	c9                   	leaveq 
    13b1:	c3                   	retq   
    13b2:	66 2e 0f 1f 84 00 00 	nopw   %cs:0x0(%rax,%rax,1)
    13b9:	00 00 00 
    13bc:	0f 1f 40 00          	nopl   0x0(%rax)

00000000000013c0 <__libc_csu_init>:
    13c0:	41 57                	push   %r15
    13c2:	4c 8d 3d 1f 2a 00 00 	lea    0x2a1f(%rip),%r15        # 3de8 <__frame_dummy_init_array_entry>
    13c9:	41 56                	push   %r14
    13cb:	49 89 d6             	mov    %rdx,%r14
    13ce:	41 55                	push   %r13
    13d0:	49 89 f5             	mov    %rsi,%r13
    13d3:	41 54                	push   %r12
    13d5:	41 89 fc             	mov    %edi,%r12d
    13d8:	55                   	push   %rbp
    13d9:	48 8d 2d 10 2a 00 00 	lea    0x2a10(%rip),%rbp        # 3df0 <__do_global_dtors_aux_fini_array_entry>
    13e0:	53                   	push   %rbx
    13e1:	4c 29 fd             	sub    %r15,%rbp
    13e4:	48 83 ec 08          	sub    $0x8,%rsp
    13e8:	e8 13 fc ff ff       	callq  1000 <_init>
    13ed:	48 c1 fd 03          	sar    $0x3,%rbp
    13f1:	74 1b                	je     140e <__libc_csu_init+0x4e>
    13f3:	31 db                	xor    %ebx,%ebx
    13f5:	0f 1f 00             	nopl   (%rax)
    13f8:	4c 89 f2             	mov    %r14,%rdx
    13fb:	4c 89 ee             	mov    %r13,%rsi
    13fe:	44 89 e7             	mov    %r12d,%edi
    1401:	41 ff 14 df          	callq  *(%r15,%rbx,8)
    1405:	48 83 c3 01          	add    $0x1,%rbx
    1409:	48 39 dd             	cmp    %rbx,%rbp
    140c:	75 ea                	jne    13f8 <__libc_csu_init+0x38>
    140e:	48 83 c4 08          	add    $0x8,%rsp
    1412:	5b                   	pop    %rbx
    1413:	5d                   	pop    %rbp
    1414:	41 5c                	pop    %r12
    1416:	41 5d                	pop    %r13
    1418:	41 5e                	pop    %r14
    141a:	41 5f                	pop    %r15
    141c:	c3                   	retq   
    141d:	0f 1f 00             	nopl   (%rax)

0000000000001420 <__libc_csu_fini>:
    1420:	c3                   	retq   

Disassembly of section .fini:

0000000000001424 <_fini>:
    1424:	48 83 ec 08          	sub    $0x8,%rsp
    1428:	48 83 c4 08          	add    $0x8,%rsp
    142c:	c3                   	retq   
