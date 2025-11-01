### Standard Operating Procedure for Project Organization

**Document ID:** SOP-PROJ-001  
**Owner:** Project Owner  
**Version:** 1.0  
**Date:** 2025-10-12

---

### Purpose and Scope

**Purpose:** Define the organization, responsibilities, workflows, and controls required to manage product development projects.
**Scope:** Applies to all personnel directly involved in design, firmware, test, manufacturing, quality, and documentation for prototype and small-batch production projects.

---

### Roles and Responsibilities

| Role | Primary Responsibilities |
| --- | --- |
| Project Owner | Set project objectives; approve scope, budgets, and major design changes |
| Design Lead | Create and control schematics and PCB designs; maintain design decision log |
| Firmware Lead | Develop firmware; manage build artifacts and OTA packaging |
| QA Lead | Maintain QMS artifacts; manage test plans, FAI, and nonconformance actions |
| Manufacturing Lead | Manage suppliers, incoming inspection, assembly, and FAI execution |
| Document Owner | Maintain assigned MDL entries and controlled records |
| Team Members | Execute assigned tasks; record evidence in assigned document repositories |

---

### Project Structure and Phases

1. Initiation  
   - Create Project Charter and PRD.  
   - Assign roles and owners.  
   - Create project folder and initial MDL entries.

2. Definition  
   - Finalize functional and safety requirements.  
   - Populate TRACEABILITY_MATRIX.csv mapping requirements to design items.  
   - Agree acceptance criteria and test plan outline.

3. Design and Development  
   - Produce schematics, PCB layout, and BOM.  
   - Implement firmware skeleton and CI build.  
   - Conduct design reviews and record minutes in DESIGN_DECISIONS.md.

4. Verification and Validation  
   - Execute test cases per test-plan.md.  
   - Record results in /test/test-logs.  
   - Perform FAI and incoming inspection per MDL-004.

5. Release and Production  
   - Approve release via Change Control.  
   - Create release artifact in /releases with controlled PDFs.  
   - Execute pilot production and update MDL records.

6. Closeout  
   - Archive final documents, update MDL and CHANGE_LOG.md.  
   - Conduct lessons learned and management review.

---

### Document Control and Repositories

| Item | Requirement |
| --- | --- |
| Controlled Documents | All MDL items listed in MDL-007 must be kept in /docs or /releases as controlled PDFs with filename convention YYYYMMDD_CODE_TITLE_V{major}.{minor}.pdf |
| Repository Structure | All projects will be organized into the /_Projects folder with the following format of mmddyyyyxx where xx is the project generation sequence of that given day. Each project folder will be organized with a folder structure as described. /Datasheets will contain any relevant information on specific components /Firmware will house any related firmware for the project /Hardware will house the schematic and PCB layout files as well as the generated BOMs /ProjectDocuments will house the files associated with project management  |
| Commits and Versioning | Commit messages must reference MDL codes when changing controlled documents. Tag releases with semantic versioning and attach MDL entries |
| Access and Permissions | Owners assign edit rights. Controlled documents require owner approval for publication |

---

### Meetings and Reviews

| Meeting | Frequency | Attendees | Purpose / Output |
| --- | --- | --- | --- |
| Weekly Team Sync | Weekly (30 min) | Design Lead, Firmware Lead, QA Lead, Manufacturing Lead, Project Owner | Progress, blockers, action items |
| Design Review | Milestone-based | Design Lead, QA Lead, Project Owner, external reviewer | Review of design artifacts; minutes in DESIGN_DECISIONS.md |
| Management Review | Quarterly | Management, Quality Owner | QMS performance, nonconformances, resource needs; minutes in MDL-024 |
| FAI Readiness Checkpoint | Before pilot production | QA, Manufacturing | Sign-off on FAI checklist |

---

### Change Control and Nonconformance

| Process | Steps |
| --- | --- |
| Change Request | Submit CCR using MDL-005. Include rationale, affected items, risk impact, verification plan, and owner |
| Approval Workflow | Design Owner and QA Owner review; Project Owner approves major changes. Document ECN in MDL-005 and update TRACEABILITY_MATRIX.csv |
| Nonconformance Handling | Log NCM entries in MDL-006 with root cause and corrective action. Track closure and verification in MDL-006 |

---

### Traceability and Records

| Record Type | Location | Retention |
| --- | --- | --- |
| Traceability Matrix | /docs/TRACEABILITY_MATRIX.csv | Permanent |
| BOM with supplier & lot | /docs/MDL-002_BOM_template.csv | 7 years |
| ERC/DRC reports | /kicad/outputs | 7 years |
| FAI photos and results | /docs/MDL-004_Incoming_Inspection_FAI.md | 7 years |
| Test logs and firmware artifacts | /test/test-logs; /firmware/builds | 7 years |
| Change control records | /docs/MDL-005_Change_Control.md | 7 years |

**Evidence Capture:** Attach test logs, photos, and signed checklists to the associated MDL entries and store in /releases for audited releases.

---

### Metrics and KPIs

| Metric | Target |
| --- | --- |
| Schedule Adherence | 90% for prototype milestones |
| First Pass Yield at FAI | 100% critical items |
| Corrective Action Turnaround | Median < 14 days for majors |
| OTA Success Rate | > 95% across test runs |

---

### Escalation Path

1. Tier 1: Raise issue to immediate owner and log in project tracker.  
2. Tier 2: If unresolved within 48 hours escalate to Project Owner.  
3. Tier 3: For critical risks or resource conflicts escalate to Management Review.

---

### Training and Competency

| Activity | Requirement |
| --- | --- |
| Onboarding | New team members must review MDL-001 through MDL-005 and sign training record in MDL-022 |
| Competency Checks | QA owner conducts periodic competency assessments on key procedures including FAI and change control |

---

### Continuous Improvement

- Capture lessons learned after each phase and log action items in MDL-023.  
- Review process effectiveness during Management Review and update SOPs as required.

---

### Revision History

| Version | Date | Author | Summary |
| --- | --- | --- | --- |
| 1.0 | 2025-10-12 | Quality Owner | Initial SOP for project organization |