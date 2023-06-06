--
-- PostgreSQL database cluster dump
--

-- Started on 2023-05-15 22:49:08

SET default_transaction_read_only = off;

SET client_encoding = 'UTF8';
SET standard_conforming_strings = on;

--
-- Roles
--

CREATE ROLE postgres;
ALTER ROLE postgres WITH SUPERUSER INHERIT CREATEROLE CREATEDB LOGIN REPLICATION BYPASSRLS PASSWORD 'SCRAM-SHA-256$4096:nOmjHrNPdaIcnCeed7FgbQ==$U+pukPiYK1tBvbNsPjn4d9zV4IXLekf/OMW5+ZDzgrY=:1f9vBcPgoAcX5hmUUOkjkXLp0FRCqsnlQRmYs2U29pU=';

--
-- User Configurations
--








--
-- Databases
--

--
-- Database "template1" dump
--

\connect template1

--
-- PostgreSQL database dump
--

-- Dumped from database version 15.2
-- Dumped by pg_dump version 15.2

-- Started on 2023-05-15 22:49:08

SET statement_timeout = 0;
SET lock_timeout = 0;
SET idle_in_transaction_session_timeout = 0;
SET client_encoding = 'UTF8';
SET standard_conforming_strings = on;
SELECT pg_catalog.set_config('search_path', '', false);
SET check_function_bodies = false;
SET xmloption = content;
SET client_min_messages = warning;
SET row_security = off;

-- Completed on 2023-05-15 22:49:08

--
-- PostgreSQL database dump complete
--

--
-- Database "mydb" dump
--

--
-- PostgreSQL database dump
--

-- Dumped from database version 15.2
-- Dumped by pg_dump version 15.2

-- Started on 2023-05-15 22:49:08

SET statement_timeout = 0;
SET lock_timeout = 0;
SET idle_in_transaction_session_timeout = 0;
SET client_encoding = 'UTF8';
SET standard_conforming_strings = on;
SELECT pg_catalog.set_config('search_path', '', false);
SET check_function_bodies = false;
SET xmloption = content;
SET client_min_messages = warning;
SET row_security = off;

--
-- TOC entry 3362 (class 1262 OID 16565)
-- Name: mydb; Type: DATABASE; Schema: -; Owner: postgres
--

CREATE DATABASE mydb WITH TEMPLATE = template0 ENCODING = 'UTF8' LOCALE_PROVIDER = libc LOCALE = 'en_US.utf8';


ALTER DATABASE mydb OWNER TO postgres;

\connect mydb

SET statement_timeout = 0;
SET lock_timeout = 0;
SET idle_in_transaction_session_timeout = 0;
SET client_encoding = 'UTF8';
SET standard_conforming_strings = on;
SELECT pg_catalog.set_config('search_path', '', false);
SET check_function_bodies = false;
SET xmloption = content;
SET client_min_messages = warning;
SET row_security = off;

SET default_tablespace = '';

SET default_table_access_method = heap;

--
-- TOC entry 215 (class 1259 OID 16574)
-- Name: users; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.users (
    id integer NOT NULL,
    login character varying(255),
    password character varying(255),
    username character varying(255)
);


ALTER TABLE public.users OWNER TO postgres;

--
-- TOC entry 214 (class 1259 OID 16573)
-- Name: Users_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public."Users_id_seq"
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public."Users_id_seq" OWNER TO postgres;

--
-- TOC entry 3363 (class 0 OID 0)
-- Dependencies: 214
-- Name: Users_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public."Users_id_seq" OWNED BY public.users.id;


--
-- TOC entry 219 (class 1259 OID 16613)
-- Name: metricstat; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.metricstat (
    id integer NOT NULL,
    solution_id integer,
    text_based_res real,
    token_based_res real,
    tree_based_res real,
    verdict boolean,
    mean_res real
);


ALTER TABLE public.metricstat OWNER TO postgres;

--
-- TOC entry 221 (class 1259 OID 16626)
-- Name: metricstat_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public.metricstat_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    MAXVALUE 2147483647
    CACHE 1;


ALTER TABLE public.metricstat_id_seq OWNER TO postgres;

--
-- TOC entry 3364 (class 0 OID 0)
-- Dependencies: 221
-- Name: metricstat_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public.metricstat_id_seq OWNED BY public.metricstat.id;


--
-- TOC entry 217 (class 1259 OID 16583)
-- Name: solutions; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.solutions (
    id integer NOT NULL,
    send_date date NOT NULL,
    sender_id integer,
    source character varying,
    task_id integer,
    result character varying,
    tokens character varying,
    asttree character varying,
    original_solution_id integer,
    language character varying(255)
);


ALTER TABLE public.solutions OWNER TO postgres;

--
-- TOC entry 216 (class 1259 OID 16582)
-- Name: solutions_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public.solutions_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.solutions_id_seq OWNER TO postgres;

--
-- TOC entry 3365 (class 0 OID 0)
-- Dependencies: 216
-- Name: solutions_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public.solutions_id_seq OWNED BY public.solutions.id;


--
-- TOC entry 218 (class 1259 OID 16598)
-- Name: tasks; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.tasks (
    id integer NOT NULL,
    description text,
    treshold real,
    name character varying(255)
);


ALTER TABLE public.tasks OWNER TO postgres;

--
-- TOC entry 220 (class 1259 OID 16623)
-- Name: tasks_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public.tasks_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    MAXVALUE 2147483647
    CACHE 1;


ALTER TABLE public.tasks_id_seq OWNER TO postgres;

--
-- TOC entry 3366 (class 0 OID 0)
-- Dependencies: 220
-- Name: tasks_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public.tasks_id_seq OWNED BY public.tasks.id;


--
-- TOC entry 3191 (class 2604 OID 16628)
-- Name: metricstat id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.metricstat ALTER COLUMN id SET DEFAULT nextval('public.metricstat_id_seq'::regclass);


--
-- TOC entry 3189 (class 2604 OID 16586)
-- Name: solutions id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.solutions ALTER COLUMN id SET DEFAULT nextval('public.solutions_id_seq'::regclass);


--
-- TOC entry 3190 (class 2604 OID 16625)
-- Name: tasks id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.tasks ALTER COLUMN id SET DEFAULT nextval('public.tasks_id_seq'::regclass);


--
-- TOC entry 3188 (class 2604 OID 16577)
-- Name: users id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.users ALTER COLUMN id SET DEFAULT nextval('public."Users_id_seq"'::regclass);


--
-- TOC entry 3354 (class 0 OID 16613)
-- Dependencies: 219
-- Data for Name: metricstat; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.metricstat (id, solution_id, text_based_res, token_based_res, tree_based_res, verdict, mean_res) FROM stdin;
0	0	1	1	1	t	1
\.


--
-- TOC entry 3352 (class 0 OID 16583)
-- Dependencies: 217
-- Data for Name: solutions; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.solutions (id, send_date, sender_id, source, task_id, result, tokens, asttree, original_solution_id, language) FROM stdin;
0	2023-05-02	0	0.1	0	0.1	0.1	0.1	0 unknown
\.


--
-- TOC entry 3353 (class 0 OID 16598)
-- Dependencies: 218
-- Data for Name: tasks; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.tasks (id, description, treshold, name) FROM stdin;
2	other_description	0.1 second_task
1	description	0.5 first_task
0   zero 0 zero
\.


--
-- TOC entry 3350 (class 0 OID 16574)
-- Dependencies: 215
-- Data for Name: users; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.users (id, login, password, username) FROM stdin;
0   deleted_user 0000 DELETED_USER
1	qwerty200468@gmail.com	123	tolik
\.


--
-- TOC entry 3367 (class 0 OID 0)
-- Dependencies: 214
-- Name: Users_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public."Users_id_seq"', 1, true);


--
-- TOC entry 3368 (class 0 OID 0)
-- Dependencies: 221
-- Name: metricstat_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public.metricstat_id_seq', 1, true);


--
-- TOC entry 3369 (class 0 OID 0)
-- Dependencies: 216
-- Name: solutions_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public.solutions_id_seq', 1, true);


--
-- TOC entry 3370 (class 0 OID 0)
-- Dependencies: 220
-- Name: tasks_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public.tasks_id_seq', 1, true);


--
-- TOC entry 3193 (class 2606 OID 16581)
-- Name: users Users_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.users
    ADD CONSTRAINT "Users_pkey" PRIMARY KEY (id);


--
-- TOC entry 3202 (class 2606 OID 16617)
-- Name: metricstat metricStat_pk; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.metricstat
    ADD CONSTRAINT "metricStat_pk" PRIMARY KEY (id);


--
-- TOC entry 3198 (class 2606 OID 16588)
-- Name: solutions solutions_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.solutions
    ADD CONSTRAINT solutions_pkey PRIMARY KEY (id);


--
-- TOC entry 3200 (class 2606 OID 16604)
-- Name: tasks tasks_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.tasks
    ADD CONSTRAINT tasks_pkey PRIMARY KEY (id);


--
-- TOC entry 3194 (class 1259 OID 16637)
-- Name: fki_original_solution_id; Type: INDEX; Schema: public; Owner: postgres
--

CREATE INDEX fki_original_solution_id ON public.solutions USING btree (original_solution_id);


--
-- TOC entry 3195 (class 1259 OID 16594)
-- Name: fki_sender_id; Type: INDEX; Schema: public; Owner: postgres
--

CREATE INDEX fki_sender_id ON public.solutions USING btree (sender_id);


--
-- TOC entry 3196 (class 1259 OID 16610)
-- Name: fki_task_id; Type: INDEX; Schema: public; Owner: postgres
--

CREATE INDEX fki_task_id ON public.solutions USING btree (task_id);


--
-- TOC entry 3203 (class 2606 OID 16632)
-- Name: solutions original_solution_id; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.solutions
    ADD CONSTRAINT original_solution_id FOREIGN KEY (original_solution_id) REFERENCES public.solutions(id) ON UPDATE CASCADE ON DELETE CASCADE NOT VALID;


--
-- TOC entry 3204 (class 2606 OID 16589)
-- Name: solutions sender_id; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.solutions
    ADD CONSTRAINT sender_id FOREIGN KEY (sender_id) REFERENCES public.users(id) ON UPDATE RESTRICT ON DELETE CASCADE NOT VALID;


--
-- TOC entry 3206 (class 2606 OID 16618)
-- Name: metricstat solutions_id; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.metricstat
    ADD CONSTRAINT solutions_id FOREIGN KEY (solution_id) REFERENCES public.solutions(id);


--
-- TOC entry 3205 (class 2606 OID 16605)
-- Name: solutions task_id; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.solutions
    ADD CONSTRAINT task_id FOREIGN KEY (task_id) REFERENCES public.tasks(id) NOT VALID;


-- Completed on 2023-05-15 22:49:09

--
-- PostgreSQL database dump complete
--

--
-- Database "postgres" dump
--

\connect postgres

--
-- PostgreSQL database dump
--

-- Dumped from database version 15.2
-- Dumped by pg_dump version 15.2

-- Started on 2023-05-15 22:49:09

SET statement_timeout = 0;
SET lock_timeout = 0;
SET idle_in_transaction_session_timeout = 0;
SET client_encoding = 'UTF8';
SET standard_conforming_strings = on;
SELECT pg_catalog.set_config('search_path', '', false);
SET check_function_bodies = false;
SET xmloption = content;
SET client_min_messages = warning;
SET row_security = off;

--
-- TOC entry 8 (class 2615 OID 16398)
-- Name: pgagent; Type: SCHEMA; Schema: -; Owner: postgres
--

CREATE SCHEMA pgagent;


ALTER SCHEMA pgagent OWNER TO postgres;

--
-- TOC entry 3437 (class 0 OID 0)
-- Dependencies: 8
-- Name: SCHEMA pgagent; Type: COMMENT; Schema: -; Owner: postgres
--

COMMENT ON SCHEMA pgagent IS 'pgAgent system tables';


--
-- TOC entry 2 (class 3079 OID 16384)
-- Name: adminpack; Type: EXTENSION; Schema: -; Owner: -
--

CREATE EXTENSION IF NOT EXISTS adminpack WITH SCHEMA pg_catalog;


--
-- TOC entry 3438 (class 0 OID 0)
-- Dependencies: 2
-- Name: EXTENSION adminpack; Type: COMMENT; Schema: -; Owner: 
--

COMMENT ON EXTENSION adminpack IS 'administrative functions for PostgreSQL';


--
-- TOC entry 3 (class 3079 OID 16399)
-- Name: pgagent; Type: EXTENSION; Schema: -; Owner: -
--

CREATE EXTENSION IF NOT EXISTS pgagent WITH SCHEMA pgagent;


--
-- TOC entry 3439 (class 0 OID 0)
-- Dependencies: 3
-- Name: EXTENSION pgagent; Type: COMMENT; Schema: -; Owner: 
--

COMMENT ON EXTENSION pgagent IS 'A PostgreSQL job scheduler';


--
-- TOC entry 3218 (class 0 OID 16400)
-- Dependencies: 219
-- Data for Name: pga_jobagent; Type: TABLE DATA; Schema: pgagent; Owner: postgres
--

COPY pgagent.pga_jobagent (jagpid, jaglogintime, jagstation) FROM stdin;
7380	2023-05-09 17:32:50.44529+03	DESKTOP-CLI5MDC
\.


--
-- TOC entry 3219 (class 0 OID 16409)
-- Dependencies: 221
-- Data for Name: pga_jobclass; Type: TABLE DATA; Schema: pgagent; Owner: postgres
--

COPY pgagent.pga_jobclass (jclid, jclname) FROM stdin;
\.


--
-- TOC entry 3220 (class 0 OID 16419)
-- Dependencies: 223
-- Data for Name: pga_job; Type: TABLE DATA; Schema: pgagent; Owner: postgres
--

COPY pgagent.pga_job (jobid, jobjclid, jobname, jobdesc, jobhostagent, jobenabled, jobcreated, jobchanged, jobagentid, jobnextrun, joblastrun) FROM stdin;
\.


--
-- TOC entry 3222 (class 0 OID 16467)
-- Dependencies: 227
-- Data for Name: pga_schedule; Type: TABLE DATA; Schema: pgagent; Owner: postgres
--

COPY pgagent.pga_schedule (jscid, jscjobid, jscname, jscdesc, jscenabled, jscstart, jscend, jscminutes, jschours, jscweekdays, jscmonthdays, jscmonths) FROM stdin;
\.


--
-- TOC entry 3223 (class 0 OID 16495)
-- Dependencies: 229
-- Data for Name: pga_exception; Type: TABLE DATA; Schema: pgagent; Owner: postgres
--

COPY pgagent.pga_exception (jexid, jexscid, jexdate, jextime) FROM stdin;
\.


--
-- TOC entry 3224 (class 0 OID 16509)
-- Dependencies: 231
-- Data for Name: pga_joblog; Type: TABLE DATA; Schema: pgagent; Owner: postgres
--

COPY pgagent.pga_joblog (jlgid, jlgjobid, jlgstatus, jlgstart, jlgduration) FROM stdin;
\.


--
-- TOC entry 3221 (class 0 OID 16443)
-- Dependencies: 225
-- Data for Name: pga_jobstep; Type: TABLE DATA; Schema: pgagent; Owner: postgres
--

COPY pgagent.pga_jobstep (jstid, jstjobid, jstname, jstdesc, jstenabled, jstkind, jstcode, jstconnstr, jstdbname, jstonerror, jscnextrun) FROM stdin;
\.


--
-- TOC entry 3225 (class 0 OID 16525)
-- Dependencies: 233
-- Data for Name: pga_jobsteplog; Type: TABLE DATA; Schema: pgagent; Owner: postgres
--

COPY pgagent.pga_jobsteplog (jslid, jsljlgid, jsljstid, jslstatus, jslresult, jslstart, jslduration, jsloutput) FROM stdin;
\.


-- Completed on 2023-05-15 22:49:09

--
-- PostgreSQL database dump complete
--

-- Completed on 2023-05-15 22:49:09

--
-- PostgreSQL database cluster dump complete
--
