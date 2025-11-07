### Standard Operating Procedure — Approved Suppliers

**Document ID:** SOP-SUPP-001  
**Owner:** Manufacturing Lead  
**Version:** 1.0  
**Date:** 2025-11-06

---

### Purpose and Scope

**Purpose:** Establish a consistent process to qualify, approve, monitor, and manage suppliers for parts, assemblies, and services used in our products.  
**Scope:** Applies to all suppliers providing components, PCBs, assembly, test services, and critical tooling for prototype and small-batch production.

---

### Definitions

| Term | Definition |
| --- | --- |
| Approved Supplier | Supplier that has completed qualification and is authorized to supply parts or services listed in the Master BOM (MDL-002) |
| Preferred Supplier | Approved supplier with demonstrated performance and strategic alignment |
| Supplier Nonconformance (NCM) | Any delivered item or service that fails to meet specified requirements (see MDL-006) |
| FAI | First Article Inspection per MDL-004 |

---

### Roles and Responsibilities

| Role | Responsibilities |
| --- | --- |
| Manufacturing Lead | Lead supplier qualification, maintain supplier list, approve purchase orders to approved suppliers |
| QA Lead | Perform supplier audits, review supplier documentation, approve supplier for critical items |
| Procurement / Ops | Execute purchase orders, collect supplier evidence, track deliveries and lot info |
| Design Lead | Define technical requirements, review supplier sample parts for fit/function |
| Quality Owner | Final approval for changes to Master Supplier List and major supplier escalations |

---

### Supplier Qualification Criteria

| Category | Minimum Evidence Required |
| --- | --- |
| Passive/Standard Components | Manufacturer datasheet; traceable MPN; certificate of conformity (CoC) or test report |
| Modules (ESP32, DRV8825) | Manufacturer datasheet; recommended land pattern; distributor traceability; CoC |
| PCBs | Fabrication spec, IPC class, sample PCB, FAI photos, copper/thickness confirmation |
| Assembly / Test Services | Process flow, ESD controls, solder profile, equipment list, references |
| Critical / Safety Items | Full technical dossier, inspection reports, and supplier FAI before first lot acceptance |

---

### Supplier Approval Process (Step-by-step)

1. Request for Supplier (RFS)  
   - Procurement creates RFS form with required part(s), estimated volume, criticality level, and target lead-time. Reference: MDL-014 Supplier List.

2. Initial Screening  
   - Verify business credentials, lead times, minimum order quantities, and basic compliance (RoHS, REACH if applicable).

3. Technical Review  
   - Design Lead reviews part datasheets, footprints, and mechanical compatibility. For modules, request manufacturer layout and recommended reflow profile.

4. Sample / Trial Order  
   - Place a small sample order or request engineering samples. Document lot, MPN, supplier name.

5. First Article Inspection (FAI) / Verification  
   - Perform FAI per MDL-004 for mechanical and electrical acceptance. Capture photos and measurements.

6. QA Review and Approval  
   - QA Lead reviews FAI and test evidence. If acceptable, supplier is added to Master Supplier List as "Approved" with scope and restrictions.

7. Supplier Onboarding  
   - Add supplier contact, approved part numbers, qualifying documents, lead times, and risk notes to `/manufacturing/supplier-list.csv` and MDL-014.

8. Issue Approved Supplier Notice  
   - Notify Procurement and update MDL-002 (BOM) to lock approved supplier for the part.

---

### Ongoing Supplier Monitoring

| Activity | Frequency | Owner | Trigger |
| --- | --- | --- | --- |
| Delivery Quality Review | Per delivery | Procurement + QA | Each lot received |
| Lot Acceptance / Incoming Inspection | Each lot | Manufacturing | Using MDL-004 checklist |
| Annual Supplier Review | Annually | QA Lead | Performance metrics review |
| Supplier Audit (on-site or remote) | As needed (critical suppliers) | QA Lead | Major nonconformance or strategic supplier |
| Performance Scoring | Quarterly | Procurement | On-time delivery, quality, responsiveness |

Performance metrics to track: On-time Delivery (%), Lot Acceptance Rate (%), Corrective Actions opened, Lead-time variance, Price stability.

---

### Supplier Change Control

| Change Type | Required Action |
| --- | --- |
| Supplier Change for Approved BOM Item | Submit CCR (MDL-005); risk assessment and verification testing; QA approval required |
| Temporary Alternate Supplier | Procurement may approve for single lot with documented verification and notification to Design & QA |
| Permanent Alternate or Supplier Removal | CCR with full justification; FAI required for new supplier; update MDL-014 and MDL-002 |

---

### Nonconformance and Corrective Action

- Record any supplier-related nonconformance in MDL-006 (NCM log).  
- Issue supplier rejection or containment instructions and quarantine material per MDL-004.  
- For critical suppliers, open CAPA and track to closure; supplier performance may be downgraded or removed on repeated failures.

---

### Records and Documentation

| Document | Location | Retention |
| --- | --- | --- |
| Supplier List (approved & preferred) | /manufacturing/supplier-list.csv | 7 years |
| Supplier Qualification Package | /manufacturing/supplier-qual/{supplier}/ | 7 years |
| Purchase Orders and Delivery Records | /procurement/purchase-orders/ | 7 years |
| FAI Records | /docs/MDL-004_Incoming_Inspection_FAI.md and /test/test-logs/ | 7 years |
| Supplier Audit Reports | /docs/MDL-023_Internal_Audits.md | 7 years |
| NCM / CAPA Records | /docs/MDL-006_Nonconformance_CAPA.md | 7 years |

All records must reference supplier name, part MPN, lot number, dates, and owner.

---

### Metrics and KPIs

| KPI | Target |
| --- | --- |
| On-time Delivery | > 95% |
| Lot Acceptance Rate | > 98% |
| Critical Supplier Escapes | 0 per year |
| Supplier Corrective Action Closure Time | Median < 14 days |

---

### Exceptions and Escalation

- For urgent production needs, Procurement may approve a single-lot temporary supplier with documented verification; notify QA and Design within 24 hours.  
- Escalate unresolved quality risks to Quality Owner; Management Review if critical supplier risk remains open after 14 days.

---

### Review and Continuous Improvement

- QA Lead conducts annual supplier performance reviews and updates supplier status (Approved / Preferred / Conditional / Removed).  
- Lessons learned from supplier issues are added to MDL-009 Design Decisions and MDL-023 Internal Audits for process improvement.

---

### Revision History

| Version | Date | Author | Summary |
| --- | --- | --- | --- |
| 1.0 | 2025-11-06 | Manufacturing Lead | Initial SOP for Approved Suppliers |