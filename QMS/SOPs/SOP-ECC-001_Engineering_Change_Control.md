### Standard Operating Procedure — Engineering Change Control (ECC)

**Document ID:** SOP-ECC-001  
**Owner:** Quality Owner  
**Version:** 1.0  
**Date:** 2026-01-10

---

### Purpose and Scope

**Purpose:**  
Define the standardized process for requesting, reviewing, approving, implementing, and documenting engineering changes to hardware, firmware, documentation, and manufacturing processes.

**Scope:**  
Applies to all controlled items including schematics, PCB layouts, firmware, BOMs, test procedures, SOPs, and manufacturing instructions for any products or services provided.

---

### Definitions

| Term | Definition |
| --- | --- |
| Engineering Change Request (ECR) | Proposal to modify a design, document, or process |
| Engineering Change Notice (ECN) | Approved change with implementation instructions |
| Controlled Document | Any item listed in MDL‑007 requiring version control |
| Major Change | Impacts form, fit, function, safety, or regulatory compliance |
| Minor Change | Cosmetic or documentation-only change with no functional impact |

---

### Roles and Responsibilities

| Role | Responsibilities |
| --- | --- |
| Design Lead | Creates ECRs for hardware/firmware changes; provides technical justification |
| QA Lead | Evaluates risk, ensures traceability, updates MDL records |
| Manufacturing Lead | Reviews impact on assembly, test, and suppliers |
| Procurement | Updates supplier records and BOM sourcing if required |
| Project Owner | Approves major changes and release readiness |
| Document Owner | Updates controlled documents and ensures correct versioning |

---

### When an Engineering Change is Required

An ECR must be initiated when any of the following occur:

- Component substitution or end‑of‑life (EOL)  
- PCB layout changes (routing, footprint, stack‑up)  
- Firmware behavior changes affecting functionality or safety  
- BOM changes (MPN, supplier, quantity, tolerance)  
- Test procedure updates  
- SOP or MDL updates  
- Corrective actions from NCM or CAPA  
- Field failure requiring design modification  

---

### Engineering Change Workflow

1. **Submit Engineering Change Request (ECR)**  
   - Use MDL‑005 template.  
   - Include:  
     - Description of change  
     - Reason / problem statement  
     - Affected documents (schematic, PCB, BOM, firmware, SOPs)  
     - Risk assessment  
     - Proposed verification plan  
     - Required implementation date  

2. **Initial Review**  
   - Design Lead and QA Lead review technical validity and risk.  
   - Manufacturing Lead reviews impact on assembly and test.  
   - Procurement reviews supplier or sourcing impact.

3. **Classification of Change**  
   - **Major Change:** Requires Project Owner approval.  
   - **Minor Change:** Approved by Design Lead + QA Lead.

4. **Approval and ECN Creation**  
   - QA Lead issues an **Engineering Change Notice (ECN)**.  
   - ECN includes:  
     - Approved change description  
     - Implementation instructions  
     - Updated document list  
     - Effective date  
     - Required re‑testing or FAI  

5. **Implementation**  
   - Document Owners update controlled documents.  
   - Version numbers incremented per versioning rules.  
   - Updated files stored in `/docs` or `/releases` as controlled PDFs.  
   - Firmware builds tagged and archived.

6. **Verification and Validation**  
   - Execute verification plan defined in ECR.  
   - Update test logs and traceability matrix (MDL‑008).  
   - Perform FAI if hardware changes are involved.

7. **Release and Communication**  
   - Notify all stakeholders (Design, QA, Manufacturing, Procurement).  
   - Update BOM, supplier list, and test procedures if applicable.  
   - Archive ECN in MDL‑005.

8. **Closeout**  
   - QA Lead confirms implementation and verification complete.  
   - Mark ECR/ECN as “Closed” in MDL‑005.

---

### Documentation Requirements

| Record | Location | Retention |
| --- | --- | --- |
| ECR / ECN Forms | /docs/MDL-005_Change_Control.md | Permanent |
| Updated Controlled Documents | /docs or /releases | 7 years |
| Verification Evidence | /test/test-logs/ | 7 years |
| Updated Traceability Matrix | /docs/MDL-008_TRACEABILITY_MATRIX.csv | Permanent |
| Supplier Updates | /manufacturing/supplier-list.csv | 7 years |

---

### Versioning Rules

| Document Type | Versioning Method |
| --- | --- |
| Hardware (schematic/PCB) | Major.Minor (e.g., V1.2 → V2.0 for major changes) |
| Firmware | Semantic versioning (e.g., 1.4.2) |
| SOPs / MDLs | Increment minor for edits; major for process changes |
| Test Procedures | Increment minor for edits; major for new test coverage |

---

### KPIs

| KPI | Target |
| --- | --- |
| ECR Review Time | < 5 business days |
| ECN Implementation Time | < 14 days for minor; < 30 days for major |
| Documentation Accuracy | 100% of ECNs reflected in MDL‑007 |
| Change Escape Rate | 0 undocumented changes |

---

### Escalation Path

1. **Design Lead → QA Lead** for risk or verification concerns  
2. **QA Lead → Project Owner** for major changes or delays  
3. **Project Owner → Management Review** for unresolved or systemic issues  

---

### Revision History

| Version | Date | Author | Summary |
| --- | --- | --- | --- |
| 1.0 | 2025-11-06 | Quality Owner | Initial SOP for engineering change control |
