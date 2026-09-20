# Estado verificado

92/135 candidatas exactas; 10,816/6,040,516 bytes de código (0.179058%).

El porcentaje incluye todo el código ejecutable del EBOOT, incluidas bibliotecas. No cuenta pseudocódigo, ensamblado ni similitud parcial.

Los porcentajes por grupo se refieren a sus funciones inventariadas. Solo el menú principal tiene un intervalo continuo completo inventariado.

## SceneTitleMainmenu

Intervalo continuo inventariado: 0x00372A38..0x00376248, 40 funciones; límites de objeto original pendientes.

| Dirección | Función | Bytes | Resultado |
|---|---|---:|---|
| `0x00372A38` | FUN_00372a38 | 708 | Sin candidata C/C++ |
| `0x00372CFC` | FUN_00372cfc | 700 | Sin candidata C/C++ |
| `0x00372FB8` | FUN_00372fb8 | 356 | Sin candidata C/C++ |
| `0x0037311C` | SceneTitleMainmenu_InitializeState | 468 | NO MATCH: 111/117 palabras; objeto 468 bytes |
| `0x003732F0` | SceneTitleMainmenu_InitializeMain | 564 | NO MATCH: 15/141 palabras; objeto 536 bytes |
| `0x00373524` | SceneTitleMainmenu_InitializeDifficulty | 336 | EXACTO |
| `0x00373674` | SceneTitleMainmenu_InitializeVs | 276 | EXACTO |
| `0x00373788` | SceneTitleMainmenu_InitializeCoop | 260 | EXACTO |
| `0x0037388C` | SceneTitleMainmenu_ConfirmExit | 196 | EXACTO |
| `0x00373950` | SceneTitleMainmenu_StoryPrompt | 212 | EXACTO |
| `0x00373A24` | SceneTitleMainmenu_InitializePremium | 348 | EXACTO |
| `0x00373B80` | SceneTitleMainmenu_InitializeExtra | 412 | EXACTO |
| `0x00373D1C` | SceneTitleMainmenu_ExtraResetPrompt | 344 | NO MATCH: 8/86 palabras; objeto 332 bytes |
| `0x00373E74` | SceneTitleMainmenu_InitializeConnect | 108 | NO MATCH: 3/27 palabras; objeto 116 bytes |
| `0x00373EE0` | SceneTitleMainmenu_ConnectionPrompt | 220 | NO MATCH: 3/55 palabras; objeto 212 bytes |
| `0x00373FBC` | SceneTitleMainmenu_PremiumSelectPrompt | 336 | EXACTO |
| `0x0037410C` | SceneTitleMainmenu_InitializeKumite | 484 | EXACTO |
| `0x003742F0` | SceneTitleMainmenu_ShowNextUnlock | 524 | EXACTO |
| `0x003744FC` | SceneTitleMainmenu_ConfirmKumiteExit | 196 | EXACTO |
| `0x003745C0` | SceneTitleMainmenu_PremiumPrompt | 204 | EXACTO |
| `0x0037468C` | SceneTitleMainmenu_MainPrompt | 204 | EXACTO |
| `0x00374758` | SceneTitleMainmenu_ConnectionWarning | 232 | NO MATCH: 13/58 palabras; objeto 228 bytes |
| `0x00374840` | SceneTitleMainmenu_CursorPosition | 100 | EXACTO |
| `0x003748A4` | SceneTitleMainmenu_CursorMotion | 72 | EXACTO |
| `0x003748EC` | SceneTitleMainmenu_BindRows | 180 | NO MATCH: 31/45 palabras; objeto 180 bytes |
| `0x003749A0` | SceneTitleMainmenu_LayoutRows | 284 | NO MATCH: 45/71 palabras; objeto 284 bytes |
| `0x00374ABC` | SceneTitleMainmenu_ResetRowColors | 240 | NO MATCH: 2/60 palabras; objeto 140 bytes |
| `0x00374BAC` | SceneTitleMainmenu_PrepareCommonScene | 156 | EXACTO |
| `0x00374C48` | SceneTitleMainmenu_IsNewStory | 40 | EXACTO |
| `0x00374C70` | SceneTitleMainmenu_HasExtra | 40 | EXACTO |
| `0x00374C98` | SceneTitleMainmenu_IsPremiumStory | 44 | EXACTO |
| `0x00374CC4` | SceneTitleMainmenu_VisibleCount | 52 | EXACTO |
| `0x00374CF8` | SceneTitleMainmenu_ExtraHasNewContent | 176 | EXACTO |
| `0x00374DA8` | SceneTitleMainmenu_KumiteHasNewContent | 160 | EXACTO |
| `0x00374E48` | SceneTitleMainmenu_HasRemainingUnlocks | 248 | EXACTO |
| `0x00374F40` | SceneTitleMainmenu_VisibleBaseY | 24 | EXACTO |
| `0x00374F58` | FUN_00374f58 | 916 | Sin candidata C/C++ |
| `0x003752EC` | SceneTitleMainmenu_Frame | 820 | EXACTO |
| `0x00375620` | SceneTitleMainmenu_ProcessInput | 2944 | NO MATCH: 665/736 palabras; objeto 2944 bytes |
| `0x003761A0` | SceneTitleMainmenu_InitializeStatics | 168 | EXACTO |

## SceneTitleBase selection helpers

Inventario parcial de dependencias reconstruidas; no representa todas las funciones del objeto original.

| Dirección | Función | Bytes | Resultado |
|---|---|---:|---|
| `0x003693BC` | TitleSelection_003693BC | 12 | EXACTO |
| `0x003693C8` | TitleSelection_SaveMenuSelection | 20 | EXACTO |
| `0x003693DC` | TitleSelection_GetMainSelection | 12 | EXACTO |
| `0x003693E8` | TitleSelection_GetSubSelection | 12 | EXACTO |
| `0x003693F4` | TitleSelection_003693F4 | 12 | EXACTO |
| `0x00369400` | TitleSelection_00369400 | 12 | EXACTO |
| `0x0036940C` | TitleSelection_0036940C | 12 | EXACTO |
| `0x00369418` | TitleSelection_00369418 | 12 | EXACTO |
| `0x00369424` | TitleSelection_SetMode0To2 | 32 | EXACTO |
| `0x00369444` | TitleSelection_GetMode | 12 | EXACTO |

## SceneCommon

Inventario parcial de dependencias reconstruidas; no representa todas las funciones del objeto original.

| Dirección | Función | Bytes | Resultado |
|---|---|---:|---|
| `0x00389338` | SceneCommon_Destroy | 52 | EXACTO |
| `0x0038936C` | SceneCommon_PrepareRenderState | 168 | EXACTO |
| `0x00389414` | SceneCommon_AreNodesComplete | 156 | NO MATCH: 15/39 palabras; objeto 148 bytes |
| `0x003894B0` | SceneCommon_IsNodeTreeComplete | 72 | EXACTO |
| `0x003894F8` | SceneCommon_SetAllNodeFrames | 124 | NO MATCH: 25/31 palabras; objeto 124 bytes |
| `0x00389574` | SceneCommon_SetNodeFrame | 64 | EXACTO |
| `0x003895B4` | SceneCommon_ResetNodeFrame | 44 | EXACTO |
| `0x003895E0` | SceneCommon_PlayNodeMotion | 68 | EXACTO |
| `0x00389624` | SceneCommon_SetNodeHidden | 56 | EXACTO |
| `0x0038965C` | SceneCommon_SetNodePosition | 72 | EXACTO |
| `0x003896A4` | SceneCommon_WrapIndex | 76 | NO MATCH: 6/19 palabras; objeto 60 bytes |
| `0x003896F0` | SceneCommon_InitializeState | 64 | NO MATCH: 9/16 palabras; objeto 64 bytes |
| `0x00389730` | SceneCommon_RequestState | 68 | EXACTO |
| `0x00389774` | SceneCommon_IsTransitionActive | 112 | NO MATCH: 24/28 palabras; objeto 112 bytes |
| `0x003897E4` | SceneCommon_PollTransition | 160 | NO MATCH: 26/40 palabras; objeto 164 bytes |
| `0x003899F4` | SceneCommon_FormatNumberPair | 192 | EXACTO |
| `0x00389AB4` | SceneCommon_PlaySound | 48 | EXACTO |

## CseNode

Inventario parcial de dependencias reconstruidas; no representa todas las funciones del objeto original.

| Dirección | Función | Bytes | Resultado |
|---|---|---:|---|
| `0x0032BB54` | CseNode_IsAnimationComplete | 40 | EXACTO |
| `0x0032BB7C` | CseNode_IsAnimationTreeComplete | 192 | NO MATCH: 47/48 palabras; objeto 192 bytes |
| `0x0032BC3C` | CseNode_SetTreeFrame | 100 | EXACTO |
| `0x0032BCA0` | CseNode_SetLocalFrame | 176 | EXACTO |
| `0x0032BD50` | CseNode_ResetMatrix | 28 | EXACTO |
| `0x0032BD6C` | CseNode_SetScale | 12 | EXACTO |
| `0x0032BD78` | CseNode_SetRotation | 8 | EXACTO |
| `0x0032BD80` | CseNode_SetPosition | 28 | EXACTO |
| `0x0032BD9C` | CseNode_GetColor | 48 | EXACTO |
| `0x0032BDCC` | CseNode_SetTreeColor | 176 | NO MATCH: 2/44 palabras; objeto 168 bytes |
| `0x0032BE7C` | CseNode_SetLocalColor | 88 | NO MATCH: 16/22 palabras; objeto 88 bytes |
| `0x0032BED4` | CseNode_SetTreeColors | 176 | NO MATCH: 2/44 palabras; objeto 168 bytes |
| `0x0032BF84` | CseNode_SetLocalColors | 96 | NO MATCH: 16/24 palabras; objeto 96 bytes |
| `0x0032BFE4` | CseNode_IsHidden | 48 | NO MATCH: 9/12 palabras; objeto 48 bytes |
| `0x0032C014` | CseNode_SetTreeHidden | 176 | NO MATCH: 8/44 palabras; objeto 172 bytes |
| `0x0032C0C4` | CseNode_SetLocalHidden | 44 | EXACTO |
| `0x0032C4EC` | CseNode_GetAnimationId | 24 | EXACTO |
| `0x0032C504` | CseNode_VirtualNoop | 8 | EXACTO |

## MenuSelector

Inventario parcial de dependencias reconstruidas; no representa todas las funciones del objeto original.

| Dirección | Función | Bytes | Resultado |
|---|---|---:|---|
| `0x002E0A6C` | MenuSelector_Configure | 72 | EXACTO |
| `0x002E0AB4` | MenuSelector_VirtualNoop | 8 | EXACTO |
| `0x002E0ABC` | MenuSelector_Update | 156 | EXACTO |
| `0x002E0B58` | MenuSelector_GetScrollOffset | 180 | NO MATCH: 6/45 palabras; objeto 180 bytes |
| `0x002E0C0C` | MenuSelector_Reset | 36 | EXACTO |
| `0x002E0C30` | MenuSelector_SetSelection | 456 | NO MATCH: 4/114 palabras; objeto 480 bytes |
| `0x002E0DF8` | MenuSelector_ReadRepeatMovement | 456 | NO MATCH: 19/114 palabras; objeto 464 bytes |
| `0x002E0FC0` | MenuSelector_ReadPressMovement | 256 | NO MATCH: 53/64 palabras; objeto 256 bytes |
| `0x002E10C0` | MenuSelector_ApplyMovement | 540 | EXACTO |
| `0x002E12DC` | MenuSelector_SetDisplayedPosition | 300 | EXACTO |
| `0x002E1408` | MenuSelector_SetFirstVisible | 76 | EXACTO |
| `0x002E1454` | MenuSelector_WrapSelection | 196 | NO MATCH: 46/49 palabras; objeto 196 bytes |
| `0x002E1518` | MenuSelector_ResetMovement | 28 | EXACTO |

## AudioEvents

Inventario parcial de dependencias reconstruidas; no representa todas las funciones del objeto original.

| Dirección | Función | Bytes | Resultado |
|---|---|---:|---|
| `0x00311F78` | AudioEvents_PlayEvent | 184 | NO MATCH: 20/46 palabras; objeto 176 bytes |
| `0x00312030` | AudioEvents_PlayGroupEvent | 200 | NO MATCH: 22/50 palabras; objeto 192 bytes |
| `0x003120F8` | AudioEvents_PlayByName | 52 | EXACTO |
| `0x0031212C` | AudioEvents_PlayGroupByName | 68 | EXACTO |
| `0x00312170` | AudioEvents_ScheduleHandleParameter | 68 | EXACTO |
| `0x003121B4` | AudioEvents_BeginHandleParameter | 100 | EXACTO |
| `0x00312218` | AudioEvents_SetHandleParameter | 32 | EXACTO |
| `0x00312238` | AudioEvents_SetCategoryParameter | 28 | EXACTO |
| `0x00312254` | AudioEvents_StopEvent | 120 | EXACTO |
| `0x003122CC` | AudioEvents_StopGroupEvent | 120 | EXACTO |
| `0x00312344` | AudioEvents_StopByName | 68 | EXACTO |
| `0x00312388` | AudioEvents_StopGroupByName | 84 | EXACTO |
| `0x003123DC` | AudioEvents_StopHandle | 68 | NO MATCH: 5/17 palabras; objeto 64 bytes |
| `0x00312420` | AudioEvents_StopCategoryFrames | 76 | NO MATCH: 17/19 palabras; objeto 76 bytes |
| `0x0031246C` | AudioEvents_StopEventFrames | 128 | EXACTO |


Los límites de TU son agrupaciones provisionales basadas en RTTI, vtables y continuidad del código. Las certificaciones compilan una función seleccionada con `MATCH_FUNCTION`; la TU enlazada completa aún no está verificada.

Regeneración: `python tools/update_status.py`, después de ejecutar `tools/audit_matches.py` sin `--only`.
