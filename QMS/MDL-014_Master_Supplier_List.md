### MDL-014 — Master Supplier List (Framework)

| Supplier ID | Supplier Name | Country | Contact | Parts Supplied (MPN list) | Approval Status | Approval Date | Qualification Notes | Lead Time (days) | MOQ | Risk Level | Owner | Documents Path |
| --- | --- | --- | --- | --- | --- | --- | --- | ---: | ---: | --- | --- | --- |
| SUP-001 | Espressif Systems (or authorized module distributor) | CN | sales@espressif.com | ESP32-WROOM-32; ESP32-S2 | Approved | 2025-10-05 | Manufacturer datasheet, reference layout, CoC on file | 14 | 100 | Low | Design Lead | /manufacturing/supplier-qual/espressif/ |
| SUP-002 | Texas Instruments (or authorized DRV distributor) | US | sales@ti.com | DRV8825 (TI/Pololu MPN variants) | Approved | 2025-10-06 | Datasheet, thermal profile; sample parts passed FAI | 10 | 50 | Low | Design Lead | /manufacturing/supplier-qual/ti-drv/ |
| SUP-003 | Local PCB Fab Co. | US | contact@localpcb.com | PCB Fabrication (2-layer, 1.6mm, HASL/ENIG) | Approved | 2025-10-12 | IPC class, sample PCB, copper thickness verified in FAI | 14 | 10 | Medium | Manufacturing Lead | /manufacturing/supplier-qual/localpcb/ |
| SUP-004 | Contract Assembly House | US | ops@asmhouse.com | PCB assembly (SMT, THT, 0201 capable) | Conditional | 2025-10-20 | Process flow and solder profile reviewed; trial run required | 21 | 10 | Medium | Manufacturing Lead | /manufacturing/supplier-qual/asmhouse/ |
| SUP-005 | Digi-Key Electronics | US | support@digikey.com | Passives; connectors; regulators (MPN list in dossier) | Preferred | 2025-10-05 | Distributor traceability and lot reporting; rapid fulfillment | 3 | 1 | Low | Procurement | /manufacturing/supplier-qual/digikey/ |
| SUP-006 | PCB Stencil Supplier | US | sales@stencils.com | Solder paste stencils | Approved | 2025-10-15 | Dimensional inspection report; alignment fixtures provided | 10 | 5 | Low | Manufacturing Lead | /manufacturing/supplier-qual/stencil/ |
| SUP-007 | Thermal Interface Supplier | CN | sales@thermco.com | Heatsinks, thermal pads | Approved | 2025-10-18 | Material certs and dimensional samples on file | 14 | 10 | Low | Manufacturing Lead | /manufacturing/supplier-qual/thermco/ |
| SUP-008 | Contract Test Lab (EMC pretest) | US | lab@emctest.com | EMC pre-cert testing services | Approved | 2025-10-22 | Scope of work and test capability verified; NDA on file | 21 | N/A | Medium | QA Lead | /manufacturing/supplier-qual/emc-lab/ |

---

Notes for use:
- Add full MPN lists and supporting qualification files to each supplier's folder under /manufacturing/supplier-qual/{supplier}/.  
- Update Approval Status to "Preferred", "Approved", "Conditional", or "Removed" and record CCRs for any changes.  
- Track lot numbers and CoC files in procurement records for each PO.  