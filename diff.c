static NORETURN void die_want_option(const char *option_name)
{
	die(_("option '%s' requires a value"), option_name);
}
	if (!strcasecmp(var, "context") || !strcasecmp(var, "plain"))
	if (!strcasecmp(var, "meta"))
		return DIFF_METAINFO;
	if (!strcasecmp(var, "frag"))
		return DIFF_FRAGINFO;
	if (!strcasecmp(var, "old"))
		return DIFF_FILE_OLD;
	if (!strcasecmp(var, "new"))
		return DIFF_FILE_NEW;
	if (!strcasecmp(var, "commit"))
		return DIFF_COMMIT;
	if (!strcasecmp(var, "whitespace"))
		return DIFF_WHITESPACE;
	if (!strcasecmp(var, "func"))
		return DIFF_FUNCINFO;
	return -1;
			DIFF_OPT_CLR(options, DIRSTAT_BY_LINE);
			DIFF_OPT_CLR(options, DIRSTAT_BY_FILE);
			DIFF_OPT_SET(options, DIRSTAT_BY_LINE);
			DIFF_OPT_CLR(options, DIRSTAT_BY_FILE);
			DIFF_OPT_CLR(options, DIRSTAT_BY_LINE);
			DIFF_OPT_SET(options, DIRSTAT_BY_FILE);
			DIFF_OPT_CLR(options, DIRSTAT_CUMULATIVE);
			DIFF_OPT_SET(options, DIRSTAT_CUMULATIVE);
static int git_config_rename(const char *var, const char *value)
	diff_detect_rename_default = 1;
	if (starts_with(var, "submodule."))
		return parse_submodule_config_option(var, value);

	external_diff_cmd = getenv("GIT_EXTERNAL_DIFF");
	struct tempfile tempfile;
typedef unsigned long (*sane_truncate_fn)(char *line, unsigned long len);

	sane_truncate_fn truncate;
static int fill_mmfile(mmfile_t *mf, struct diff_filespec *one)
	else if (diff_populate_filespec(one, 0))
static unsigned long diff_filespec_size(struct diff_filespec *one)
	diff_populate_filespec(one, CHECK_SIZE_ONLY);
static void emit_line_0(struct diff_options *o, const char *set, const char *reset,
	int nofirst;
	if (len == 0) {
		has_trailing_newline = (first == '\n');
		has_trailing_carriage_return = (!has_trailing_newline &&
						(first == '\r'));
		nofirst = has_trailing_newline || has_trailing_carriage_return;
	} else {
		has_trailing_newline = (len > 0 && line[len-1] == '\n');
		if (has_trailing_newline)
			len--;
		has_trailing_carriage_return = (len > 0 && line[len-1] == '\r');
		if (has_trailing_carriage_return)
			len--;
		nofirst = 0;
	if (len || !nofirst) {
		if (!nofirst)
			fputc(first, file);
		fwrite(line, len, 1, file);
	}
	emit_line_0(o, set, reset, line[0], line+1, len-1);
static int new_blank_line_at_eof(struct emit_callback *ecbdata, const char *line, int len)
	if (!((ecbdata->ws_rule & WS_BLANK_AT_EOF) &&
	      ecbdata->blank_at_eof_in_preimage &&
	      ecbdata->blank_at_eof_in_postimage &&
	      ecbdata->blank_at_eof_in_preimage <= ecbdata->lno_in_preimage &&
	      ecbdata->blank_at_eof_in_postimage <= ecbdata->lno_in_postimage))
	return ws_blank_line(line, len, ecbdata->ws_rule);
static void emit_line_checked(const char *reset,
			      struct emit_callback *ecbdata,
			      const char *line, int len,
			      enum color_diff color,
			      unsigned ws_error_highlight,
			      char sign)
	const char *set = diff_get_color(ecbdata->color_diff, color);
	if (ecbdata->opt->ws_error_highlight & ws_error_highlight) {
		ws = diff_get_color(ecbdata->color_diff, DIFF_WHITESPACE);
	if (!ws)
		emit_line_0(ecbdata->opt, set, reset, sign, line, len);
	else if (sign == '+' && new_blank_line_at_eof(ecbdata, line, len))
		emit_line_0(ecbdata->opt, ws, reset, sign, line, len);
		emit_line_0(ecbdata->opt, set, reset, sign, "", 0);
		ws_check_emit(line, len, ecbdata->ws_rule,
			      ecbdata->opt->file, set, reset, ws);
static void emit_add_line(const char *reset,
			  struct emit_callback *ecbdata,
	emit_line_checked(reset, ecbdata, line, len,
			  DIFF_FILE_NEW, WSEH_NEW, '+');
static void emit_del_line(const char *reset,
			  struct emit_callback *ecbdata,
	emit_line_checked(reset, ecbdata, line, len,
			  DIFF_FILE_OLD, WSEH_OLD, '-');
static void emit_context_line(const char *reset,
			      struct emit_callback *ecbdata,
	emit_line_checked(reset, ecbdata, line, len,
			  DIFF_CONTEXT, WSEH_CONTEXT, ' ');
		emit_line(ecbdata->opt, context, reset, line, len);
	strbuf_add(&msgbuf, line, ep - line);
	emit_line(ecbdata->opt, "", "", msgbuf.buf, msgbuf.len);
static struct diff_tempfile *claim_diff_tempfile(void) {
	die("BUG: diff is failing to clean up its tempfiles");
		if (is_tempfile_active(&diff_temp[i].tempfile))
static void print_line_count(FILE *file, int count)
		fprintf(file, "0,0");
		fprintf(file, "1");
		fprintf(file, "1,%d", count);
	static const char *nneof = " No newline at end of file\n";
	const char *reset = diff_get_color(ecb->color_diff, DIFF_RESET);
			emit_del_line(reset, ecb, data, len);
			emit_add_line(reset, ecb, data, len);
	if (!endp) {
		const char *context = diff_get_color(ecb->color_diff,
						     DIFF_CONTEXT);
		putc('\n', ecb->opt->file);
		emit_line_0(ecb->opt, context, reset, '\\',
			    nneof, strlen(nneof));
	}
	const char *name_a_tab, *name_b_tab;
	const char *metainfo = diff_get_color(o->use_color, DIFF_METAINFO);
	const char *fraginfo = diff_get_color(o->use_color, DIFF_FRAGINFO);
	const char *reset = diff_get_color(o->use_color, DIFF_RESET);
	const char *line_prefix = diff_line_prefix(o);
	if (diff_mnemonic_prefix && DIFF_OPT_TST(o, REVERSE_DIFF)) {
	name_a_tab = strchr(name_a, ' ') ? "\t" : "";
	name_b_tab = strchr(name_b, ' ') ? "\t" : "";
	size_one = fill_textconv(textconv_one, one, &data_one);
	size_two = fill_textconv(textconv_two, two, &data_two);
	ecbdata.ws_rule = whitespace_rule(name_b);
	fprintf(o->file,
		"%s%s--- %s%s%s\n%s%s+++ %s%s%s\n%s%s@@ -",
		line_prefix, metainfo, a_name.buf, name_a_tab, reset,
		line_prefix, metainfo, b_name.buf, name_b_tab, reset,
		line_prefix, fraginfo);
		print_line_count(o->file, lc_a);
		fprintf(o->file, "?,?");
	fprintf(o->file, " +");
	print_line_count(o->file, lc_b);
	fprintf(o->file, " @@%s\n", reset);
	struct diff_words_style_elem new, old, ctx;
static int fn_out_diff_words_write_helper(FILE *fp,
					  size_t count, const char *buf,
					  const char *line_prefix)
			fputs(line_prefix, fp);
			if (st_el->color && fputs(st_el->color, fp) < 0)
				return -1;
			if (fputs(st_el->prefix, fp) < 0 ||
			    fwrite(buf, p ? p - buf : count, 1, fp) != 1 ||
			    fputs(st_el->suffix, fp) < 0)
				return -1;
			if (st_el->color && *st_el->color
			    && fputs(GIT_COLOR_RESET, fp) < 0)
				return -1;
			return 0;
		if (fputs(newline, fp) < 0)
			return -1;
static void fn_out_diff_words_aux(void *priv, char *line, unsigned long len)
	int minus_first, minus_len, plus_first, plus_len;
	if (line[0] != '@' || parse_hunk_header(line, len,
			&minus_first, &minus_len, &plus_first, &plus_len))
		return;

		fn_out_diff_words_write_helper(diff_words->opt->file,
				diff_words->current_plus, line_prefix);
		if (*(plus_begin - 1) == '\n')
			fputs(line_prefix, diff_words->opt->file);
		fn_out_diff_words_write_helper(diff_words->opt->file,
				&style->old, style->newline,
				minus_end - minus_begin, minus_begin,
				line_prefix);
		fn_out_diff_words_write_helper(diff_words->opt->file,
				&style->new, style->newline,
				plus_end - plus_begin, plus_begin,
				line_prefix);
		fputs(line_prefix, diff_words->opt->file);
		fn_out_diff_words_write_helper(diff_words->opt->file,
			&style->old, style->newline,
			diff_words->minus.text.ptr, line_prefix);
	if (xdi_diff_outf(&minus, &plus, fn_out_diff_words_aux, diff_words,
			  &xpp, &xecfg))
			fputs(line_prefix, diff_words->opt->file);
		fn_out_diff_words_write_helper(diff_words->opt->file,
			- diff_words->current_plus, diff_words->current_plus,
			line_prefix);
static void diff_filespec_load_driver(struct diff_filespec *one)
		one->driver = userdiff_find_by_path(one->path);
static const char *userdiff_word_regex(struct diff_filespec *one)
	diff_filespec_load_driver(one);
		o->word_regex = userdiff_word_regex(one);
		o->word_regex = userdiff_word_regex(two);
			die ("Invalid regular expression: %s",
			     o->word_regex);
		st->old.color = diff_get_color_opt(o, DIFF_FILE_OLD);
		st->new.color = diff_get_color_opt(o, DIFF_FILE_NEW);
static unsigned long sane_truncate_line(struct emit_callback *ecb, char *line, unsigned long len)
	if (ecb->truncate)
		return ecb->truncate(line, len);
	const char *meta = diff_get_color(ecbdata->color_diff, DIFF_METAINFO);
	const char *context = diff_get_color(ecbdata->color_diff, DIFF_CONTEXT);
	const char *reset = diff_get_color(ecbdata->color_diff, DIFF_RESET);
	const char *line_prefix = diff_line_prefix(o);
		fprintf(o->file, "%s", ecbdata->header->buf);
		const char *name_a_tab, *name_b_tab;

		name_a_tab = strchr(ecbdata->label_path[0], ' ') ? "\t" : "";
		name_b_tab = strchr(ecbdata->label_path[1], ' ') ? "\t" : "";

		fprintf(o->file, "%s%s--- %s%s%s\n",
			line_prefix, meta, ecbdata->label_path[0], reset, name_a_tab);
		fprintf(o->file, "%s%s+++ %s%s%s\n",
			line_prefix, meta, ecbdata->label_path[1], reset, name_b_tab);
		len = sane_truncate_line(ecbdata, line, len);
		if (line[len-1] != '\n')
			putc('\n', o->file);
		if (ecbdata->diff_words->type == DIFF_WORDS_PORCELAIN) {
			emit_line(o, context, reset, line, len);
			fputs("~\n", o->file);
		} else {
			/*
			 * Skip the prefix character, if any.  With
			 * diff_suppress_blank_empty, there may be
			 * none.
			 */
			if (line[0] != '\n') {
			      line++;
			      len--;
			}
			emit_line(o, context, reset, line, len);
		}
		emit_add_line(reset, ecbdata, line + 1, len - 1);
		emit_del_line(reset, ecbdata, line + 1, len - 1);
		emit_context_line(reset, ecbdata, line + 1, len - 1);
		emit_line(o, diff_get_color(ecbdata->color_diff, DIFF_CONTEXT),
			  reset, line, len);
static char *pprint_rename(const char *a, const char *b)
	const char *old = a;
	const char *new = b;
	struct strbuf name = STRBUF_INIT;
		quote_c_style(a, &name, NULL, 0);
		strbuf_addstr(&name, " => ");
		quote_c_style(b, &name, NULL, 0);
		return strbuf_detach(&name, NULL);
	while (*old && *new && *old == *new) {
		if (*old == '/')
			pfx_length = old - a + 1;
		old++;
		new++;
	old = a + len_a;
	new = b + len_b;
	while (a + pfx_length - pfx_adjust_for_slash <= old &&
	       b + pfx_length - pfx_adjust_for_slash <= new &&
	       *old == *new) {
		if (*old == '/')
			sfx_length = len_a - (old - a);
		old--;
		new--;
	strbuf_grow(&name, pfx_length + a_midlen + b_midlen + sfx_length + 7);
		strbuf_add(&name, a, pfx_length);
		strbuf_addch(&name, '{');
	strbuf_add(&name, a + pfx_length, a_midlen);
	strbuf_addstr(&name, " => ");
	strbuf_add(&name, b + pfx_length, b_midlen);
		strbuf_addch(&name, '}');
		strbuf_add(&name, a + len_a - sfx_length, sfx_length);
	}
	return strbuf_detach(&name, NULL);
}

struct diffstat_t {
	int nr;
	int alloc;
	struct diffstat_file {
		char *from_name;
		char *name;
		char *print_name;
		unsigned is_unmerged:1;
		unsigned is_binary:1;
		unsigned is_renamed:1;
		unsigned is_interesting:1;
		uintmax_t added, deleted;
	} **files;
};
static void show_name(FILE *file,
		      const char *prefix, const char *name, int len)
{
	fprintf(file, " %s%-*s |", prefix, len, name);
}

static void show_graph(FILE *file, char ch, int cnt, const char *set, const char *reset)
	fprintf(file, "%s", set);
	while (cnt--)
		putc(ch, file);
	fprintf(file, "%s", reset);
	char *pname;
	if (!file->is_renamed) {
		struct strbuf buf = STRBUF_INIT;
		if (quote_c_style(file->name, &buf, NULL, 0)) {
			pname = strbuf_detach(&buf, NULL);
		} else {
			pname = file->name;
			strbuf_release(&buf);
		}
	} else {
		pname = pprint_rename(file->from_name, file->name);
	}
	file->print_name = pname;
int print_stat_summary(FILE *fp, int files, int insertions, int deletions)
	int ret;
		return fprintf(fp, "%s\n", " 0 files changed");
	ret = fputs(sb.buf, fp);
	return ret;
	const char *line_prefix = "";
	line_prefix = diff_line_prefix(options);
			fprintf(options->file, "%s", line_prefix);
			show_name(options->file, prefix, name, len);
			fprintf(options->file, " %*s", number_width, "Bin");
				putc('\n', options->file);
			fprintf(options->file, " %s%"PRIuMAX"%s",
			fprintf(options->file, " -> ");
			fprintf(options->file, "%s%"PRIuMAX"%s",
			fprintf(options->file, " bytes");
			fprintf(options->file, "\n");
			fprintf(options->file, "%s", line_prefix);
			show_name(options->file, prefix, name, len);
			fprintf(options->file, " Unmerged\n");
		fprintf(options->file, "%s", line_prefix);
		show_name(options->file, prefix, name, len);
		fprintf(options->file, " %*"PRIuMAX"%s",
		show_graph(options->file, '+', add, add_c, reset);
		show_graph(options->file, '-', del, del_c, reset);
		fprintf(options->file, "\n");
			fprintf(options->file, "%s ...\n", line_prefix);
	fprintf(options->file, "%s", line_prefix);
	print_stat_summary(options->file, total_files, adds, dels);
		int deleted= data->files[i]->deleted;
	fprintf(options->file, "%s", diff_line_prefix(options));
	print_stat_summary(options->file, total_files, adds, dels);
	unsigned long this_dir = 0;
		unsigned long this;
			this = gather_dirstat(opt, dir, changed, f->name, newbaselen);
			this = f->changed;
		this_dir += this;
		if (this_dir) {
			int permille = this_dir * 1000 / changed;
	return this_dir;
	dir.cumulative = DIFF_OPT_TST(options, DIRSTAT_CUMULATIVE);
		int content_changed;
		if (p->one->oid_valid && p->two->oid_valid)
			content_changed = oidcmp(&p->one->oid, &p->two->oid);
		else
			content_changed = 1;

		if (!content_changed) {
		if (DIFF_OPT_TST(options, DIRSTAT_BY_FILE)) {
			diff_populate_filespec(p->one, 0);
			diff_populate_filespec(p->two, 0);
			diffcore_count_changes(p->one, p->two, NULL, NULL,
			diff_populate_filespec(p->one, CHECK_SIZE_ONLY);
			diff_populate_filespec(p->two, CHECK_SIZE_ONLY);
		 * be identical, but since content_changed is true, we
	dir.cumulative = DIFF_OPT_TST(options, DIRSTAT_CUMULATIVE);
static void free_diffstat_info(struct diffstat_t *diffstat)
		if (f->name != f->print_name)
			free(f->print_name);
	} else if (line[0] == '@') {
		char *plus = strchr(line, '+');
		if (plus)
			data->lineno = strtol(plus, NULL, 10) - 1;
		else
			die("invalid diff");
static void emit_binary_diff_body(FILE *file, mmfile_t *one, mmfile_t *two,
				  const char *prefix)
		fprintf(file, "%sdelta %lu\n", prefix, orig_size);
	}
	else {
		fprintf(file, "%sliteral %lu\n", prefix, two->size);
		char line[70];
		fprintf(file, "%s", prefix);
		fputs(line, file);
		fputc('\n', file);
	fprintf(file, "%s\n", prefix);
static void emit_binary_diff(FILE *file, mmfile_t *one, mmfile_t *two,
			     const char *prefix)
	fprintf(file, "%sGIT binary patch\n", prefix);
	emit_binary_diff_body(file, one, two, prefix);
	emit_binary_diff_body(file, two, one, prefix);
int diff_filespec_is_binary(struct diff_filespec *one)
		diff_filespec_load_driver(one);
				diff_populate_filespec(one, CHECK_BINARY);
static const struct userdiff_funcname *diff_funcname_pattern(struct diff_filespec *one)
	diff_filespec_load_driver(one);
struct userdiff_driver *get_textconv(struct diff_filespec *one)
	diff_filespec_load_driver(one);
	return userdiff_get_textconv(one->driver);
	if (DIFF_OPT_TST(o, REVERSE_DIFF)) {
		const char *del = diff_get_color_opt(o, DIFF_FILE_OLD);
		const char *add = diff_get_color_opt(o, DIFF_FILE_NEW);
		show_submodule_summary(o->file, one->path ? one->path : two->path,
				line_prefix,
				two->dirty_submodule,
				meta, del, add, reset);
		const char *del = diff_get_color_opt(o, DIFF_FILE_OLD);
		const char *add = diff_get_color_opt(o, DIFF_FILE_NEW);
		show_submodule_inline_diff(o->file, one->path ? one->path : two->path,
				line_prefix,
				two->dirty_submodule,
				meta, del, add, reset, o);
	if (DIFF_OPT_TST(o, ALLOW_TEXTCONV)) {
		textconv_one = get_textconv(one);
		textconv_two = get_textconv(two);
		    (textconv_one || !diff_filespec_is_binary(one)) &&
		    (textconv_two || !diff_filespec_is_binary(two))) {
			fprintf(o->file, "%s", header.buf);
						textconv_one, textconv_two, o);
		fprintf(o->file, "%s", header.buf);
	} else if (!DIFF_OPT_TST(o, TEXT) &&
	    ( (!textconv_one && diff_filespec_is_binary(one)) ||
	      (!textconv_two && diff_filespec_is_binary(two)) )) {
		    !DIFF_OPT_TST(o, BINARY)) {
			if (!oidcmp(&one->oid, &two->oid)) {
					fprintf(o->file, "%s", header.buf);
			fprintf(o->file, "%s", header.buf);
			fprintf(o->file, "%sBinary files %s and %s differ\n",
				line_prefix, lbl[0], lbl[1]);
		if (fill_mmfile(&mf1, one) < 0 || fill_mmfile(&mf2, two) < 0)
				fprintf(o->file, "%s", header.buf);
		fprintf(o->file, "%s", header.buf);
		if (DIFF_OPT_TST(o, BINARY))
			emit_binary_diff(o->file, &mf1, &mf2, line_prefix);
		else
			fprintf(o->file, "%sBinary files %s and %s differ\n",
				line_prefix, lbl[0], lbl[1]);
		const char *diffopts = getenv("GIT_DIFF_OPTS");
			fprintf(o->file, "%s", header.buf);
		mf1.size = fill_textconv(textconv_one, one, &mf1.ptr);
		mf2.size = fill_textconv(textconv_two, two, &mf2.ptr);
		pe = diff_funcname_pattern(one);
			pe = diff_funcname_pattern(two);
		ecbdata.ws_rule = whitespace_rule(name_b);
		ecbdata.header = header.len ? &header : NULL;
		if (DIFF_OPT_TST(o, FUNCCONTEXT))
		if (xdi_diff_outf(&mf1, &mf2, fn_out_consume, &ecbdata,
				  &xpp, &xecfg))
	same_contents = !oidcmp(&one->oid, &two->oid);
	if (diff_filespec_is_binary(one) || diff_filespec_is_binary(two)) {
			data->added = diff_filespec_size(two);
			data->deleted = diff_filespec_size(one);
		diff_populate_filespec(one, 0);
		diff_populate_filespec(two, 0);
		if (fill_mmfile(&mf1, one) < 0 || fill_mmfile(&mf2, two) < 0)
		if (xdi_diff_outf(&mf1, &mf2, diffstat_consume, diffstat,
				  &xpp, &xecfg))
	data.ws_rule = whitespace_rule(attr_path);
	data.conflict_marker_size = ll_merge_marker_size(attr_path);
	if (fill_mmfile(&mf1, one) < 0 || fill_mmfile(&mf2, two) < 0)
	if (diff_filespec_is_binary(two))
		if (xdi_diff_outf(&mf1, &mf2, checkdiff_consume, &data,
		DIFF_OPT_SET(o, CHECK_FAILED);
static int reuse_worktree_file(const char *name, const struct object_id *oid, int want_file)
	if (!active_cache)
	if (!FAST_WORKING_DIRECTORY && !want_file && has_sha1_pack(oid->hash))
	if (!want_file && would_convert_to_git(&the_index, name))
	pos = cache_name_pos(name, len);
	ce = active_cache[pos];
	if (oidcmp(oid, &ce->oid) || !S_ISREG(ce->ce_mode))
	    (!lstat(name, &st) && !ce_match_stat(ce, &st, 0)))
int diff_populate_filespec(struct diff_filespec *s, unsigned int flags)
	enum safe_crlf crlf_warn = (safe_crlf == SAFE_CRLF_FAIL
				    ? SAFE_CRLF_WARN
				    : safe_crlf);
	    reuse_worktree_file(s->path, &s->oid, 0)) {
			if (errno == ENOENT) {
			err_empty:
				err = -1;
			empty:
				s->data = (char *)"";
				s->size = 0;
				return err;
			}
		if (size_only && !would_convert_to_git(&the_index, s->path))
		if (convert_to_git(&the_index, s->path, s->data, s->size, &buf, crlf_warn)) {
			type = sha1_object_info(s->oid.hash, &s->size);
		s->data = read_sha1_file(s->oid.hash, &type, &s->size);
static void prep_temp_blob(const char *path, struct diff_tempfile *temp,
	int fd;
	struct strbuf template = STRBUF_INIT;
	strbuf_addstr(&template, "XXXXXX_");
	strbuf_addstr(&template, base);
	fd = mks_tempfile_ts(&temp->tempfile, template.buf, strlen(base) + 1);
	if (fd < 0)
	if (convert_to_working_tree(path,
	if (write_in_full(fd, blob, size) < 0)
	close_tempfile(&temp->tempfile);
	temp->name = get_tempfile_path(&temp->tempfile);
	strbuf_release(&template);
static struct diff_tempfile *prepare_temp_file(const char *name,
		struct diff_filespec *one)
	     reuse_worktree_file(name, &one->oid, 1))) {
			prep_temp_blob(name, temp, sb.buf, sb.len,
		if (diff_populate_filespec(one, 0))
		prep_temp_blob(name, temp, one->data, one->size,
static void add_external_diff_name(struct argv_array *argv,
	struct diff_tempfile *temp = prepare_temp_file(name, df);
			      int complete_rewrite,
		add_external_diff_name(&argv, name, one);
			add_external_diff_name(&argv, name, two);
			add_external_diff_name(&argv, other, two);
	if (one && one->should_munmap)
		diff_free_filespec_data(one);
	if (two && two->should_munmap)
		diff_free_filespec_data(two);
		return find_unique_abbrev(oid->hash, abbrev);
		if (abbrev > GIT_SHA1_HEXSZ)
			die("BUG: oid abbreviation out of range: %d", abbrev);
	if (one && two && oidcmp(&one->oid, &two->oid)) {
		int abbrev = DIFF_OPT_TST(o, FULL_INDEX) ? 40 : DEFAULT_ABBREV;
		if (DIFF_OPT_TST(o, BINARY)) {
			if ((!fill_mmfile(&mf, one) && diff_filespec_is_binary(one)) ||
			    (!fill_mmfile(&mf, two) && diff_filespec_is_binary(two)))
				abbrev = 40;
	if (DIFF_OPT_TST(o, ALLOW_EXTERNAL)) {
		struct userdiff_driver *drv = userdiff_find_by_path(attr_path);
		run_external_diff(pgm, name, other, one, two, xfrm_msg,
				  complete_rewrite, o);
static void diff_fill_oid_info(struct diff_filespec *one)
			if (index_path(one->oid.hash, one->path, &st, 0))
	if (*namep && **namep != '/') {
	if (*otherp && **otherp != '/') {
	name  = p->one->path;
	other = (strcmp(name, p->two->path) ? p->two->path : NULL);
	if (!DIFF_OPT_TST(o, ALLOW_EXTERNAL))
	diff_fill_oid_info(one);
	diff_fill_oid_info(two);
			     one, null, &msg, o, p);
		builtin_diffstat(p->one->path, NULL, NULL, NULL, diffstat, o, p);
	diff_fill_oid_info(p->one);
	diff_fill_oid_info(p->two);
	builtin_diffstat(name, other, p->one, p->two, diffstat, o, p);
	diff_fill_oid_info(p->one);
	diff_fill_oid_info(p->two);
void diff_setup(struct diff_options *options)
	DIFF_OPT_SET(options, RENAME_EMPTY);
	int count = 0;
	if (options->output_format & DIFF_FORMAT_NAME)
		count++;
	if (options->output_format & DIFF_FORMAT_NAME_STATUS)
		count++;
	if (options->output_format & DIFF_FORMAT_CHECKDIFF)
		count++;
	if (options->output_format & DIFF_FORMAT_NO_OUTPUT)
		count++;
	if (count > 1)
	if (DIFF_XDL_TST(options, IGNORE_WHITESPACE) ||
	    DIFF_XDL_TST(options, IGNORE_WHITESPACE_CHANGE) ||
	    DIFF_XDL_TST(options, IGNORE_WHITESPACE_AT_EOL))
		DIFF_OPT_SET(options, DIFF_FROM_CONTENTS);
		DIFF_OPT_CLR(options, DIFF_FROM_CONTENTS);
	if (DIFF_OPT_TST(options, FIND_COPIES_HARDER))
	if (!DIFF_OPT_TST(options, RELATIVE_NAME))
		DIFF_OPT_SET(options, RECURSIVE);
	if (options->pickaxe)
		DIFF_OPT_SET(options, RECURSIVE);
		DIFF_OPT_SET(options, DIRTY_SUBMODULES);
	if (options->setup & DIFF_SETUP_USE_CACHE) {
		if (!active_cache)
			/* read-cache does not die even when it fails
			 * so it is safe for us to do this here.  Also
			 * it does not smudge active_cache or active_nr
			 * when it fails, so we do not have to worry about
			 * cleaning it up ourselves either.
			 */
			read_cache();
	}
	if (40 < options->abbrev)
		options->abbrev = 40; /* full */
	if (DIFF_OPT_TST(options, QUICK)) {
		DIFF_OPT_SET(options, EXIT_WITH_STATUS);
	if (DIFF_OPT_TST(options, FOLLOW_RENAMES) && options->pathspec.nr != 1)
}

static int opt_arg(const char *arg, int arg_short, const char *arg_long, int *val)
{
	char c, *eq;
	int len;

	if (*arg != '-')
		return 0;
	c = *++arg;
	if (!c)
		return 0;
	if (c == arg_short) {
		c = *++arg;
		if (!c)
			return 1;
		if (val && isdigit(c)) {
			char *end;
			int n = strtoul(arg, &end, 10);
			if (*end)
				return 0;
			*val = n;
			return 1;
		}
		return 0;
	}
	if (c != '-')
		return 0;
	arg++;
	eq = strchrnul(arg, '=');
	len = eq - arg;
	if (!len || strncmp(arg, arg_long, len))
		return 0;
	if (*eq) {
		int n;
		char *end;
		if (!isdigit(*++eq))
			return 0;
		n = strtoul(eq, &end, 10);
		if (*end)
			return 0;
		*val = n;
	}
	return 1;
}
static int diff_scoreopt_parse(const char *opt);
static inline int short_opt(char opt, const char **argv,
			    const char **optarg)
{
	const char *arg = argv[0];
	if (arg[0] != '-' || arg[1] != opt)
		return 0;
	if (arg[2] != '\0') {
		*optarg = arg + 2;
		return 1;
	}
	if (!argv[1])
		die("Option '%c' requires a value", opt);
	*optarg = argv[1];
	return 2;
	return 2;
static int stat_opt(struct diff_options *options, const char **av)
	const char *arg = av[0];
	char *end;
	int width = options->stat_width;
	int name_width = options->stat_name_width;
	int graph_width = options->stat_graph_width;
	int count = options->stat_count;
	int argcount = 1;
	if (!skip_prefix(arg, "--stat", &arg))
		die("BUG: stat option does not begin with --stat: %s", arg);
	end = (char *)arg;
	switch (*arg) {
	case '-':
		if (skip_prefix(arg, "-width", &arg)) {
			if (*arg == '=')
				width = strtoul(arg + 1, &end, 10);
			else if (!*arg && !av[1])
				die_want_option("--stat-width");
			else if (!*arg) {
				width = strtoul(av[1], &end, 10);
				argcount = 2;
			}
		} else if (skip_prefix(arg, "-name-width", &arg)) {
			if (*arg == '=')
				name_width = strtoul(arg + 1, &end, 10);
			else if (!*arg && !av[1])
				die_want_option("--stat-name-width");
			else if (!*arg) {
				name_width = strtoul(av[1], &end, 10);
				argcount = 2;
			}
		} else if (skip_prefix(arg, "-graph-width", &arg)) {
			if (*arg == '=')
				graph_width = strtoul(arg + 1, &end, 10);
			else if (!*arg && !av[1])
				die_want_option("--stat-graph-width");
			else if (!*arg) {
				graph_width = strtoul(av[1], &end, 10);
				argcount = 2;
			}
		} else if (skip_prefix(arg, "-count", &arg)) {
			if (*arg == '=')
				count = strtoul(arg + 1, &end, 10);
			else if (!*arg && !av[1])
				die_want_option("--stat-count");
			else if (!*arg) {
				count = strtoul(av[1], &end, 10);
				argcount = 2;
			}
		}
		break;
	case '=':
		width = strtoul(arg+1, &end, 10);
		if (*end == ',')
			name_width = strtoul(end+1, &end, 10);
		if (*end == ',')
			count = strtoul(end+1, &end, 10);
	}
	/* Important! This checks all the error cases! */
	if (*end)
		return 0;
	options->output_format |= DIFF_FORMAT_DIFFSTAT;
	options->stat_name_width = name_width;
	options->stat_graph_width = graph_width;
	options->stat_width = width;
	options->stat_count = count;
	return argcount;
static int parse_dirstat_opt(struct diff_options *options, const char *params)
	struct strbuf errmsg = STRBUF_INIT;
	if (parse_dirstat_params(options, params, &errmsg))
		die(_("Failed to parse --dirstat/-X option parameter:\n%s"),
		    errmsg.buf);
	strbuf_release(&errmsg);
	/*
	 * The caller knows a dirstat-related option is given from the command
	 * line; allow it to say "return this_function();"
	 */
	options->output_format |= DIFF_FORMAT_DIRSTAT;
	return 1;
static int parse_submodule_opt(struct diff_options *options, const char *value)
	if (parse_submodule_params(options, value))
		die(_("Failed to parse --submodule option parameter: '%s'"),
			value);
	return 1;
static const char diff_status_letters[] = {
	DIFF_STATUS_ADDED,
	DIFF_STATUS_COPIED,
	DIFF_STATUS_DELETED,
	DIFF_STATUS_MODIFIED,
	DIFF_STATUS_RENAMED,
	DIFF_STATUS_TYPE_CHANGED,
	DIFF_STATUS_UNKNOWN,
	DIFF_STATUS_UNMERGED,
	DIFF_STATUS_FILTER_AON,
	DIFF_STATUS_FILTER_BROKEN,
	'\0',
};
static unsigned int filter_bit['Z' + 1];
static void prepare_filter_bits(void)
	if (!filter_bit[DIFF_STATUS_ADDED]) {
		for (i = 0; diff_status_letters[i]; i++)
			filter_bit[(int) diff_status_letters[i]] = (1 << i);
	}
static unsigned filter_bit_tst(char status, const struct diff_options *opt)
	return opt->filter & filter_bit[(int) status];
static int parse_diff_filter_opt(const char *optarg, struct diff_options *opt)
	int i, optch;
	prepare_filter_bits();
	/*
	 * If there is a negation e.g. 'd' in the input, and we haven't
	 * initialized the filter field with another --diff-filter, start
	 * from full set of bits, except for AON.
	 */
	if (!opt->filter) {
		for (i = 0; (optch = optarg[i]) != '\0'; i++) {
			if (optch < 'a' || 'z' < optch)
				continue;
			opt->filter = (1 << (ARRAY_SIZE(diff_status_letters) - 1)) - 1;
			opt->filter &= ~filter_bit[DIFF_STATUS_FILTER_AON];
			break;
		}
	}
	for (i = 0; (optch = optarg[i]) != '\0'; i++) {
		unsigned int bit;
		int negate;
		if ('a' <= optch && optch <= 'z') {
			negate = 1;
			optch = toupper(optch);
		} else {
			negate = 0;
		}
		bit = (0 <= optch && optch <= 'Z') ? filter_bit[optch] : 0;
		if (!bit)
			return optarg[i];
		if (negate)
			opt->filter &= ~bit;
		else
			opt->filter |= bit;
	}
static void enable_patch_output(int *fmt) {
	*fmt &= ~DIFF_FORMAT_NO_OUTPUT;
	*fmt |= DIFF_FORMAT_PATCH;
}

static int parse_ws_error_highlight_opt(struct diff_options *opt, const char *arg)
	int val = parse_ws_error_highlight(arg);
	if (val < 0) {
		error("unknown value after ws-error-highlight=%.*s",
		      -1 - val, arg);
		return 0;
	opt->ws_error_highlight = val;
	return 1;
int diff_opt_parse(struct diff_options *options,
		   const char **av, int ac, const char *prefix)
	const char *arg = av[0];
	const char *optarg;
	int argcount;
	if (!prefix)
		prefix = "";
	/* Output format options */
	if (!strcmp(arg, "-p") || !strcmp(arg, "-u") || !strcmp(arg, "--patch")
	    || opt_arg(arg, 'U', "unified", &options->context))
		enable_patch_output(&options->output_format);
	else if (!strcmp(arg, "--raw"))
		options->output_format |= DIFF_FORMAT_RAW;
	else if (!strcmp(arg, "--patch-with-raw")) {
		enable_patch_output(&options->output_format);
		options->output_format |= DIFF_FORMAT_RAW;
	} else if (!strcmp(arg, "--numstat"))
		options->output_format |= DIFF_FORMAT_NUMSTAT;
	else if (!strcmp(arg, "--shortstat"))
		options->output_format |= DIFF_FORMAT_SHORTSTAT;
	else if (!strcmp(arg, "-X") || !strcmp(arg, "--dirstat"))
		return parse_dirstat_opt(options, "");
	else if (skip_prefix(arg, "-X", &arg))
		return parse_dirstat_opt(options, arg);
	else if (skip_prefix(arg, "--dirstat=", &arg))
		return parse_dirstat_opt(options, arg);
	else if (!strcmp(arg, "--cumulative"))
		return parse_dirstat_opt(options, "cumulative");
	else if (!strcmp(arg, "--dirstat-by-file"))
		return parse_dirstat_opt(options, "files");
	else if (skip_prefix(arg, "--dirstat-by-file=", &arg)) {
		parse_dirstat_opt(options, "files");
		return parse_dirstat_opt(options, arg);
	}
	else if (!strcmp(arg, "--check"))
		options->output_format |= DIFF_FORMAT_CHECKDIFF;
	else if (!strcmp(arg, "--summary"))
		options->output_format |= DIFF_FORMAT_SUMMARY;
	else if (!strcmp(arg, "--patch-with-stat")) {
		enable_patch_output(&options->output_format);
		options->output_format |= DIFF_FORMAT_DIFFSTAT;
	} else if (!strcmp(arg, "--name-only"))
		options->output_format |= DIFF_FORMAT_NAME;
	else if (!strcmp(arg, "--name-status"))
		options->output_format |= DIFF_FORMAT_NAME_STATUS;
	else if (!strcmp(arg, "-s") || !strcmp(arg, "--no-patch"))
		options->output_format |= DIFF_FORMAT_NO_OUTPUT;
	else if (starts_with(arg, "--stat"))
		/* --stat, --stat-width, --stat-name-width, or --stat-count */
		return stat_opt(options, av);

	/* renames options */
	else if (starts_with(arg, "-B") || starts_with(arg, "--break-rewrites=") ||
		 !strcmp(arg, "--break-rewrites")) {
		if ((options->break_opt = diff_scoreopt_parse(arg)) == -1)
			return error("invalid argument to -B: %s", arg+2);
	}
	else if (starts_with(arg, "-M") || starts_with(arg, "--find-renames=") ||
		 !strcmp(arg, "--find-renames")) {
		if ((options->rename_score = diff_scoreopt_parse(arg)) == -1)
			return error("invalid argument to -M: %s", arg+2);
		options->detect_rename = DIFF_DETECT_RENAME;
	}
	else if (!strcmp(arg, "-D") || !strcmp(arg, "--irreversible-delete")) {
		options->irreversible_delete = 1;
	}
	else if (starts_with(arg, "-C") || starts_with(arg, "--find-copies=") ||
		 !strcmp(arg, "--find-copies")) {
		if (options->detect_rename == DIFF_DETECT_COPY)
			DIFF_OPT_SET(options, FIND_COPIES_HARDER);
		if ((options->rename_score = diff_scoreopt_parse(arg)) == -1)
			return error("invalid argument to -C: %s", arg+2);
		options->detect_rename = DIFF_DETECT_COPY;
	}
	else if (!strcmp(arg, "--no-renames"))
		options->detect_rename = 0;
	else if (!strcmp(arg, "--rename-empty"))
		DIFF_OPT_SET(options, RENAME_EMPTY);
	else if (!strcmp(arg, "--no-rename-empty"))
		DIFF_OPT_CLR(options, RENAME_EMPTY);
	else if (!strcmp(arg, "--relative"))
		DIFF_OPT_SET(options, RELATIVE_NAME);
	else if (skip_prefix(arg, "--relative=", &arg)) {
		DIFF_OPT_SET(options, RELATIVE_NAME);
		options->prefix = arg;
	/* xdiff options */
	else if (!strcmp(arg, "--minimal"))
		DIFF_XDL_SET(options, NEED_MINIMAL);
	else if (!strcmp(arg, "--no-minimal"))
		DIFF_XDL_CLR(options, NEED_MINIMAL);
	else if (!strcmp(arg, "-w") || !strcmp(arg, "--ignore-all-space"))
		DIFF_XDL_SET(options, IGNORE_WHITESPACE);
	else if (!strcmp(arg, "-b") || !strcmp(arg, "--ignore-space-change"))
		DIFF_XDL_SET(options, IGNORE_WHITESPACE_CHANGE);
	else if (!strcmp(arg, "--ignore-space-at-eol"))
		DIFF_XDL_SET(options, IGNORE_WHITESPACE_AT_EOL);
	else if (!strcmp(arg, "--ignore-blank-lines"))
		DIFF_XDL_SET(options, IGNORE_BLANK_LINES);
	else if (!strcmp(arg, "--indent-heuristic"))
		DIFF_XDL_SET(options, INDENT_HEURISTIC);
	else if (!strcmp(arg, "--no-indent-heuristic"))
		DIFF_XDL_CLR(options, INDENT_HEURISTIC);
	else if (!strcmp(arg, "--patience"))
		options->xdl_opts = DIFF_WITH_ALG(options, PATIENCE_DIFF);
	else if (!strcmp(arg, "--histogram"))
		options->xdl_opts = DIFF_WITH_ALG(options, HISTOGRAM_DIFF);
	else if ((argcount = parse_long_opt("diff-algorithm", av, &optarg))) {
		long value = parse_algorithm_value(optarg);
		if (value < 0)
			return error("option diff-algorithm accepts \"myers\", "
				     "\"minimal\", \"patience\" and \"histogram\"");
		/* clear out previous settings */
		DIFF_XDL_CLR(options, NEED_MINIMAL);
		options->xdl_opts &= ~XDF_DIFF_ALGORITHM_MASK;
		options->xdl_opts |= value;
		return argcount;
	}

	/* flags options */
	else if (!strcmp(arg, "--binary")) {
		enable_patch_output(&options->output_format);
		DIFF_OPT_SET(options, BINARY);
	}
	else if (!strcmp(arg, "--full-index"))
		DIFF_OPT_SET(options, FULL_INDEX);
	else if (!strcmp(arg, "-a") || !strcmp(arg, "--text"))
		DIFF_OPT_SET(options, TEXT);
	else if (!strcmp(arg, "-R"))
		DIFF_OPT_SET(options, REVERSE_DIFF);
	else if (!strcmp(arg, "--find-copies-harder"))
		DIFF_OPT_SET(options, FIND_COPIES_HARDER);
	else if (!strcmp(arg, "--follow"))
		DIFF_OPT_SET(options, FOLLOW_RENAMES);
	else if (!strcmp(arg, "--no-follow")) {
		DIFF_OPT_CLR(options, FOLLOW_RENAMES);
		DIFF_OPT_CLR(options, DEFAULT_FOLLOW_RENAMES);
	} else if (!strcmp(arg, "--color"))
		options->use_color = 1;
	else if (skip_prefix(arg, "--color=", &arg)) {
		int value = git_config_colorbool(NULL, arg);
		if (value < 0)
			return error("option `color' expects \"always\", \"auto\", or \"never\"");
		options->use_color = value;
	}
	else if (!strcmp(arg, "--no-color"))
		options->use_color = 0;
	else if (!strcmp(arg, "--color-words")) {
		options->use_color = 1;
		options->word_diff = DIFF_WORDS_COLOR;
	}
	else if (skip_prefix(arg, "--color-words=", &arg)) {
		options->use_color = 1;
		options->word_diff = DIFF_WORDS_COLOR;
		options->word_regex = arg;
	}
	else if (!strcmp(arg, "--word-diff")) {
		if (options->word_diff == DIFF_WORDS_NONE)
			options->word_diff = DIFF_WORDS_PLAIN;
	}
	else if (skip_prefix(arg, "--word-diff=", &arg)) {
			die("bad --word-diff argument: %s", arg);
	}
	else if ((argcount = parse_long_opt("word-diff-regex", av, &optarg))) {
		options->word_regex = optarg;
		return argcount;
	}
	else if (!strcmp(arg, "--exit-code"))
		DIFF_OPT_SET(options, EXIT_WITH_STATUS);
	else if (!strcmp(arg, "--quiet"))
		DIFF_OPT_SET(options, QUICK);
	else if (!strcmp(arg, "--ext-diff"))
		DIFF_OPT_SET(options, ALLOW_EXTERNAL);
	else if (!strcmp(arg, "--no-ext-diff"))
		DIFF_OPT_CLR(options, ALLOW_EXTERNAL);
	else if (!strcmp(arg, "--textconv"))
		DIFF_OPT_SET(options, ALLOW_TEXTCONV);
	else if (!strcmp(arg, "--no-textconv"))
		DIFF_OPT_CLR(options, ALLOW_TEXTCONV);
	else if (!strcmp(arg, "--ignore-submodules")) {
		DIFF_OPT_SET(options, OVERRIDE_SUBMODULE_CONFIG);
		handle_ignore_submodules_arg(options, "all");
	} else if (skip_prefix(arg, "--ignore-submodules=", &arg)) {
		DIFF_OPT_SET(options, OVERRIDE_SUBMODULE_CONFIG);
		handle_ignore_submodules_arg(options, arg);
	} else if (!strcmp(arg, "--submodule"))
		options->submodule_format = DIFF_SUBMODULE_LOG;
	else if (skip_prefix(arg, "--submodule=", &arg))
		return parse_submodule_opt(options, arg);
	else if (skip_prefix(arg, "--ws-error-highlight=", &arg))
		return parse_ws_error_highlight_opt(options, arg);
	else if (!strcmp(arg, "--ita-invisible-in-index"))
		options->ita_invisible_in_index = 1;
	else if (!strcmp(arg, "--ita-visible-in-index"))
		options->ita_invisible_in_index = 0;

	/* misc options */
	else if (!strcmp(arg, "-z"))
		options->line_termination = 0;
	else if ((argcount = short_opt('l', av, &optarg))) {
		options->rename_limit = strtoul(optarg, NULL, 10);
		return argcount;
	}
	else if ((argcount = short_opt('S', av, &optarg))) {
		options->pickaxe = optarg;
		options->pickaxe_opts |= DIFF_PICKAXE_KIND_S;
		return argcount;
	} else if ((argcount = short_opt('G', av, &optarg))) {
		options->pickaxe = optarg;
		options->pickaxe_opts |= DIFF_PICKAXE_KIND_G;
		return argcount;
	}
	else if (!strcmp(arg, "--pickaxe-all"))
		options->pickaxe_opts |= DIFF_PICKAXE_ALL;
	else if (!strcmp(arg, "--pickaxe-regex"))
		options->pickaxe_opts |= DIFF_PICKAXE_REGEX;
	else if ((argcount = short_opt('O', av, &optarg))) {
		options->orderfile = prefix_filename(prefix, optarg);
		return argcount;
	}
	else if ((argcount = parse_long_opt("diff-filter", av, &optarg))) {
		int offending = parse_diff_filter_opt(optarg, options);
		if (offending)
			die("unknown change class '%c' in --diff-filter=%s",
			    offending, optarg);
		return argcount;
	}
	else if (!strcmp(arg, "--no-abbrev"))
		options->abbrev = 0;
	else if (!strcmp(arg, "--abbrev"))
		options->abbrev = DEFAULT_ABBREV;
	else if (skip_prefix(arg, "--abbrev=", &arg)) {
		options->abbrev = strtoul(arg, NULL, 10);
		if (options->abbrev < MINIMUM_ABBREV)
			options->abbrev = MINIMUM_ABBREV;
		else if (40 < options->abbrev)
			options->abbrev = 40;
	}
	else if ((argcount = parse_long_opt("src-prefix", av, &optarg))) {
		options->a_prefix = optarg;
		return argcount;
	}
	else if ((argcount = parse_long_opt("line-prefix", av, &optarg))) {
		options->line_prefix = optarg;
		options->line_prefix_length = strlen(options->line_prefix);
		graph_setup_line_prefix(options);
		return argcount;
	}
	else if ((argcount = parse_long_opt("dst-prefix", av, &optarg))) {
		options->b_prefix = optarg;
		return argcount;
	}
	else if (!strcmp(arg, "--no-prefix"))
		options->a_prefix = options->b_prefix = "";
	else if (opt_arg(arg, '\0', "inter-hunk-context",
			 &options->interhunkcontext))
		;
	else if (!strcmp(arg, "-W"))
		DIFF_OPT_SET(options, FUNCCONTEXT);
	else if (!strcmp(arg, "--function-context"))
		DIFF_OPT_SET(options, FUNCCONTEXT);
	else if (!strcmp(arg, "--no-function-context"))
		DIFF_OPT_CLR(options, FUNCCONTEXT);
	else if ((argcount = parse_long_opt("output", av, &optarg))) {
		char *path = prefix_filename(prefix, optarg);
		options->file = xfopen(path, "w");
		options->close_file = 1;
		if (options->use_color != GIT_COLOR_ALWAYS)
			options->use_color = GIT_COLOR_NEVER;
		free(path);
		return argcount;
	} else
		return 0;
	return 1;
static int diff_scoreopt_parse(const char *opt)
{
	int opt1, opt2, cmd;

	if (*opt++ != '-')
		return -1;
	cmd = *opt++;
	if (cmd == '-') {
		/* convert the long-form arguments into short-form versions */
		if (skip_prefix(opt, "break-rewrites", &opt)) {
			if (*opt == 0 || *opt++ == '=')
				cmd = 'B';
		} else if (skip_prefix(opt, "find-copies", &opt)) {
			if (*opt == 0 || *opt++ == '=')
				cmd = 'C';
		} else if (skip_prefix(opt, "find-renames", &opt)) {
			if (*opt == 0 || *opt++ == '=')
				cmd = 'M';
		}
	}
	if (cmd != 'M' && cmd != 'C' && cmd != 'B')
		return -1; /* that is not a -M, -C, or -B option */

	opt1 = parse_rename_score(&opt);
	if (cmd != 'B')
		opt2 = 0;
	else {
		if (*opt == 0)
			opt2 = 0;
		else if (*opt != '/')
			return -1; /* we expect -B80/99 or -B80 */
		else {
			opt++;
			opt2 = parse_rename_score(&opt);
		}
	}
	if (*opt != 0)
		return -1;
	return opt1 | (opt2 << 16);
}

	if (len == GIT_SHA1_HEXSZ)
	 * In well-behaved cases, where the abbbreviated result is the
	if (abblen < GIT_SHA1_HEXSZ - 3) {
	    !oidcmp(&one->oid, &two->oid) &&
		else if (oidcmp(&p->one->oid, &p->two->oid) ||
static void show_file_mode_name(FILE *file, const char *newdelete, struct diff_filespec *fs)
		fprintf(file, " %s mode %06o ", newdelete, fs->mode);
		fprintf(file, " %s ", newdelete);
	write_name_quoted(fs->path, file, '\n');

static void show_mode_change(FILE *file, struct diff_filepair *p, int show_name,
		const char *line_prefix)
		fprintf(file, "%s mode change %06o => %06o%c", line_prefix, p->one->mode,
			p->two->mode, show_name ? ' ' : '\n');
			write_name_quoted(p->two->path, file, '\n');
static void show_rename_copy(FILE *file, const char *renamecopy, struct diff_filepair *p,
			const char *line_prefix)
	char *names = pprint_rename(p->one->path, p->two->path);

	fprintf(file, " %s %s (%d%%)\n", renamecopy, names, similarity_index(p));
	free(names);
	show_mode_change(file, p, 0, line_prefix);
	FILE *file = opt->file;
	const char *line_prefix = diff_line_prefix(opt);

		fputs(line_prefix, file);
		show_file_mode_name(file, "delete", p->one);
		fputs(line_prefix, file);
		show_file_mode_name(file, "create", p->two);
		fputs(line_prefix, file);
		show_rename_copy(file, "copy", p, line_prefix);
		fputs(line_prefix, file);
		show_rename_copy(file, "rename", p, line_prefix);
			fprintf(file, "%s rewrite ", line_prefix);
			write_name_quoted(p->two->path, file, ' ');
			fprintf(file, "(%d%%)\n", similarity_index(p));
		show_mode_change(file, p, !p->score, line_prefix);
	git_SHA_CTX *ctx;
	/* Ignore line numbers when computing the SHA1 of the patch */
	if (starts_with(line, "@@ -"))
		return;

	git_SHA1_Update(data->ctx, line, new_len);
static void patch_id_add_string(git_SHA_CTX *ctx, const char *str)
	git_SHA1_Update(ctx, str, strlen(str));
static void patch_id_add_mode(git_SHA_CTX *ctx, unsigned mode)
	git_SHA1_Update(ctx, buf, len);
/* returns 0 upon success, and writes result into sha1 */
static int diff_get_patch_id(struct diff_options *options, struct object_id *oid, int diff_header_only)
	git_SHA_CTX ctx;
	git_SHA1_Init(&ctx);
		diff_fill_oid_info(p->one);
		diff_fill_oid_info(p->two);
		git_SHA1_Update(&ctx, p->one->path, len1);
		git_SHA1_Update(&ctx, p->two->path, len2);
			git_SHA1_Update(&ctx, p->two->path, len2);
			git_SHA1_Update(&ctx, p->one->path, len1);
			git_SHA1_Update(&ctx, p->one->path, len1);
			git_SHA1_Update(&ctx, p->two->path, len2);
		if (fill_mmfile(&mf1, p->one) < 0 ||
		    fill_mmfile(&mf2, p->two) < 0)
		if (diff_filespec_is_binary(p->one) ||
		    diff_filespec_is_binary(p->two)) {
			git_SHA1_Update(&ctx, oid_to_hex(&p->one->oid),
					GIT_SHA1_HEXSZ);
			git_SHA1_Update(&ctx, oid_to_hex(&p->two->oid),
					GIT_SHA1_HEXSZ);
		if (xdi_diff_outf(&mf1, &mf2, patch_id_consume, &data,
				  &xpp, &xecfg))
	git_SHA1_Final(oid->hash, &ctx);
int diff_flush_patch_id(struct diff_options *options, struct object_id *oid, int diff_header_only)
	int result = diff_get_patch_id(options, oid, diff_header_only);
	if (0 < needed && needed < 32767)
	if (output_format & DIFF_FORMAT_DIRSTAT && DIFF_OPT_TST(options, DIRSTAT_BY_LINE))
		memset(&diffstat, 0, sizeof(struct diffstat_t));
		for (i = 0; i < q->nr; i++) {
			struct diff_filepair *p = q->queue[i];
			if (check_pair_status(p))
				diff_flush_stat(p, options, &diffstat);
		}
	    DIFF_OPT_TST(options, EXIT_WITH_STATUS) &&
	    DIFF_OPT_TST(options, DIFF_FROM_CONTENTS)) {
			fprintf(options->file, "%s%c",
				diff_line_prefix(options),
				options->line_termination);
			if (options->stat_sep) {
				fputs(options->stat_sep, options->file);
			}
		for (i = 0; i < q->nr; i++) {
			struct diff_filepair *p = q->queue[i];
			if (check_pair_status(p))
				diff_flush_patch(p, options);
		}
	if (DIFF_OPT_TST(options, DIFF_FROM_CONTENTS)) {
			DIFF_OPT_SET(options, HAS_CHANGES);
			DIFF_OPT_CLR(options, HAS_CHANGES);
static int diff_filespec_is_identical(struct diff_filespec *one,
	if (diff_populate_filespec(one, 0))
	if (diff_populate_filespec(two, 0))
static int diff_filespec_check_stat_unmatch(struct diff_filepair *p)
	    diff_populate_filespec(p->one, CHECK_SIZE_ONLY) ||
	    diff_populate_filespec(p->two, CHECK_SIZE_ONLY) ||
	    !diff_filespec_is_identical(p->one, p->two)) /* (2) */
		if (diff_filespec_check_stat_unmatch(p))
			if (!DIFF_OPT_TST(diffopt, NO_INDEX))
void diffcore_fix_diff_index(struct diff_options *options)
			diffcore_break(options->break_opt);
	if (options->pickaxe)
	if (diff_queued_diff.nr && !DIFF_OPT_TST(options, DIFF_FROM_CONTENTS))
		DIFF_OPT_SET(options, HAS_CHANGES);
		DIFF_OPT_CLR(options, HAS_CHANGES);
	if (!DIFF_OPT_TST(opt, EXIT_WITH_STATUS) &&
	if (DIFF_OPT_TST(opt, EXIT_WITH_STATUS) &&
	    DIFF_OPT_TST(opt, HAS_CHANGES))
	    DIFF_OPT_TST(opt, CHECK_FAILED))
	return (DIFF_OPT_TST(opt, QUICK) &&
		DIFF_OPT_TST(opt, HAS_CHANGES));
	unsigned orig_flags = options->flags;
	if (!DIFF_OPT_TST(options, OVERRIDE_SUBMODULE_CONFIG))
	if (DIFF_OPT_TST(options, IGNORE_SUBMODULES))
	if (DIFF_OPT_TST(options, REVERSE_DIFF))
	if (!DIFF_OPT_TST(options, DIFF_FROM_CONTENTS))
		DIFF_OPT_SET(options, HAS_CHANGES);
	if (DIFF_OPT_TST(options, REVERSE_DIFF)) {
	if (DIFF_OPT_TST(options, DIFF_FROM_CONTENTS))
	if (DIFF_OPT_TST(options, QUICK) && options->skip_stat_unmatch &&
	    !diff_filespec_check_stat_unmatch(p))
	DIFF_OPT_SET(options, HAS_CHANGES);
static char *run_textconv(const char *pgm, struct diff_filespec *spec,
		size_t *outsize)
	temp = prepare_temp_file(spec->path, spec);
size_t fill_textconv(struct userdiff_driver *driver,
		if (diff_populate_filespec(df, 0))
		die("BUG: fill_textconv called with non-textconv driver");
	*outbuf = run_textconv(driver->textconv, df, &size);
int textconv_object(const char *path,
	textconv = get_textconv(df);
	*buf_size = fill_textconv(textconv, df, buf);
	if (!DIFF_OPT_TST(opt, EXIT_WITH_STATUS) &&